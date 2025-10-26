from PySide6.QtCore import Qt, QAbstractListModel, QModelIndex, Signal, QSize
from PySide6.QtWidgets import (
    QApplication, QWidget, QListView, QStyledItemDelegate,
    QHBoxLayout, QLabel, QPushButton, QStyleOptionViewItem, QStyle, QSizePolicy
)
from PySide6.QtGui import QKeySequence, QUndoStack, QUndoCommand

# ---------------------------
# Custom QListView to show PLC list with custom widgets
# ---------------------------
class PlcListView(QListView):
    def __init__(self, parent=None):
        super().__init__(parent)
        # Any custom initialization for the PlcListView can go here

    def rebuild_all_widgets(self):
        """
        Remove all index widgets and recreate them to ensure correct numbering after deletions/insertions.
        Recreate widgets to ensure correct numbering after deletions/insertions.
        """
        model = self.model()
        if model is None:
            print("PlcListView: No model set, cannot rebuild widgets.")
            return

        total = model.rowCount()
        # remove any existing widgets by iterating possible indexes
        # +10 to ensure covering old widgets (safe)
        for r in range(total + 10):
            idx = model.index(r, 0)
            w = self.indexWidget(idx)
            if w is not None:
                self.setIndexWidget(idx, None)

        # create new widget for each valid index
        for row in range(total):
            idx = model.index(row, 0)
            row_info = model.rowInfo(row)

            def make_on_delete(r=row):
                return lambda: model.do_remove_item(r)

            w = RowWidget(index_number=row + 1, text=row_info, 
                          on_delete_callable=make_on_delete())
            self.setIndexWidget(idx, w)

# ---------------------------
# Model for manage the list data
# ---------------------------
class RowModel(QAbstractListModel):
    # signal to notify view to rebuild widgets
    rebuildWidgets = Signal()
    redoStateChanged = Signal(bool)
    undoStateChanged = Signal(bool)

    def __init__(self, items=None):
        super().__init__()
        self._items = items or []
        self._undo_stack = QUndoStack(self)
        self.rebuildWidgets.connect(self._check_undo_redo_signals)

    def _check_undo_redo_signals(self):
        self.undoStateChanged.emit(self._undo_stack.canUndo())
        self.redoStateChanged.emit(self._undo_stack.canRedo())

    def rowCount(self, parent=QModelIndex()):
        return len(self._items)

    def data(self, index, role=Qt.DisplayRole):
        if not index.isValid():
            return None
        if role == Qt.DisplayRole:
            # avoid return data because we use custom widgets
            return None
        return None

    def rowInfo(self, row):
        if 0 <= row < len(self._items):
            return self._items[row]
        return None
    
    def do_undo(self):
        if self._undo_stack.canUndo():
            self._undo_stack.undo()
        else:
            self.undoStateChanged.emit(False)

    def do_redo(self):
        if self._undo_stack.canRedo():
            self._undo_stack.redo()
        else:
            self.redoStateChanged.emit(False)
    
    def do_add_item(self, text: str):
        cmd = AddCommand(self, self.rowCount(), text, description=f"Add '{text}'")
        self._undo_stack.push(cmd)

    def do_remove_item(self, row: int):
        cmd = RemoveCommand(self, row, description=f"Remove row {row+1}")
        self._undo_stack.push(cmd)

    def do_edit_item(self, row: int, new_text: str):
        cmd = EditCommand(self, row, new_text, description=f"Edit row {row+1}")
        self._undo_stack.push(cmd)

    # Core mutators used by QUndoCommands
    def add_item(self, text: str):
        self.beginInsertRows(QModelIndex(), len(self._items), len(self._items))
        self._items.append(text)
        self.endInsertRows()
        self.rebuildWidgets.emit()

    def insert_item(self, row: int, text: str):
        if row < 0:
            row = 0
        if row > len(self._items):
            row = len(self._items)
        self.beginInsertRows(QModelIndex(), row, row)
        self._items.insert(row, text)
        self.endInsertRows()
        self.rebuildWidgets.emit()

    def remove_item(self, row: int):
        if row < 0 or row >= len(self._items):
            return
        self.beginRemoveRows(QModelIndex(), row, row)
        old = self._items.pop(row)
        self.endRemoveRows()
        self.rebuildWidgets.emit()
        return old 

    def set_item(self, row: int, text: str):
        if row < 0 or row >= len(self._items):
            return
        old = self._items[row]
        self._items[row] = text
        idx = self.index(row, 0)
        self.dataChanged.emit(idx, idx, [Qt.DisplayRole])
        self.rebuildWidgets.emit()
        return old

# -------------------------
# QUndoCommand implementations
# -------------------------
class AddCommand(QUndoCommand):
    def __init__(self, model: RowModel, row: int, info: str, description="Add item"):
        super().__init__(description)
        self.model = model
        self.row = row
        self.info = info

    def redo(self):
        # redo will be callded immediately after push
        # insert_item will emit rowsInserted and rebuildWidgets
        self.model.insert_item(self.row, self.info)

    def undo(self):
        # remove the row we previously added
        self.model.remove_item(self.row)

class RemoveCommand(QUndoCommand):
    def __init__(self, model: RowModel, row: int, description="Remove item"):
        super().__init__(description)
        self.model = model
        self.row = row
        self.removed_info = None

    def redo(self):
        # store removed text for undo
        self.removed_info = self.model.remove_item(self.row)

    def undo(self):
        if self.removed_info is not None:
            self.model.insert_item(self.row, self.removed_info)

class EditCommand(QUndoCommand):
    def __init__(self, model: RowModel, row: int, new_info: str, description="Edit item"):
        super().__init__(description)
        self.model = model
        self.row = row
        self.new_info = new_info
        self.old_info = None

    def redo(self):
        self.old_info = self.model.set_item(self.row, self.new_info)

    def undo(self):
        if self.old_info is not None:
            self.model.set_item(self.row, self.old_info)

# ---------------------------
# Widget for earch row in the list
# ---------------------------
class RowWidget(QWidget):
    def __init__(self, index_number: int, text: str, on_delete_callable):
        super().__init__()
        h = QHBoxLayout(self)
        h.setContentsMargins(8, 4, 8, 4)
        h.setSpacing(12)

        self.lbl_index = QLabel(f"{index_number}")        
        self.lbl_index.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        self.lbl_index.setToolTip( f"Row {index_number}: {text}")

        self.lbl_text = QLabel(text)
        self.lbl_text.setToolTip( f"Row {index_number}: {text}")

        self.btn_delete = QPushButton("Delete")
        self.btn_delete.setSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        self.btn_delete.clicked.connect(on_delete_callable)

        h.addWidget(self.lbl_index, 1)
        h.addWidget(self.lbl_text, 1)  # expand
        h.addStretch()
        h.addWidget(self.btn_delete)

# ---------------------------
# Row Delegate for tree view
# ---------------------------
class RowDelegate(QStyledItemDelegate):
    deleteRequested = Signal(int)
    
    def sizeHint(self, option, index):
        height = option.fontMetrics.height() + 12
        return QSize(0, height)
