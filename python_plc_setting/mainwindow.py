# This Python file uses the following encoding: utf-8
import sys

from PySide6.QtCore import Qt, QSize
from PySide6.QtWidgets import QApplication, QMainWindow, QListView, QVBoxLayout, QPushButton, QMessageBox
from PySide6.QtGui import QUndoStack

# Important:
# You need to run the following command to generate the ui_form.py file
#     pyside6-uic form.ui -o ui_form.py, or
#     pyside2-uic form.ui -o ui_form.py
from ui_form import Ui_MainWindow
from plc_list_view import RowModel, RowWidget, RowDelegate, AddCommand, RemoveCommand, EditCommand

class MainWindow(QMainWindow):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.ui = Ui_MainWindow()
        self.ui.setupUi(self)

        # Model
        # self.model = RowModel(["Alpha", "Bravo", "Charlie", "Delta"])
        self.model = RowModel()
        # self.model.add_item("Echo")
        # self.model.add_item("129.168.1.1")

        # View
        self.ui.listView_plc.setModel(self.model)
        self.ui.listView_plc.setItemDelegate(RowDelegate())

        self.undo_stack = QUndoStack(self)

        # Connect signals
        # self.model.rowsInserted.connect(self.ui.listView_plc.rebuild_all_widgets)
        # self.model.rowsRemoved.connect(self.ui.listView_plc.rebuild_all_widgets)
        # self.model.modelReset.connect(self.ui.listView_plc.rebuild_all_widgets)
        self.model.rebuildWidgets.connect(self.ui.listView_plc.rebuild_all_widgets)
        # self.model.undoStateChanged.connect(self.on_undo_state_changed)
        # self.model.redoStateChanged.connect(self.on_redo_state_changed)
        # self.on_undo_state_changed(False)
        # self.on_redo_state_changed(False)

        # Initial build of index widgets
        self.ui.listView_plc.rebuild_all_widgets()

        self.ui.btn_add.clicked.connect(self.on_add)
        self.ui.btn_redo.clicked.connect(self.on_redo)
        self.ui.btn_undo.clicked.connect(self.on_undo)

    def on_undo_state_changed(self, can_undo: bool):
        self.ui.btn_undo.setEnabled(can_undo)

    def on_redo_state_changed(self, can_redo: bool):
        self.ui.btn_redo.setEnabled(can_redo)
        
    def on_undo(self):
        self.model.do_undo()

    def on_redo(self):
        self.model.do_redo()

     # Example handlers that create+push commands
    def on_add(self):
        row = self.model.rowCount()
        text = f"Item {row+1}"
        self.model.do_add_item(text)
        self.ui.listView_plc.setCurrentIndex(self.model.index(row, 0))

    def on_remove(self):
        idx = self.view.currentIndex()
        if not idx.isValid():
            QMessageBox.information(self, "Select", "Please select a row to remove")
            return
        row = idx.row()
        cmd = RemoveCommand(self.model, row, description=f"Remove row {row+1}")
        self.undo_stack.push(cmd)

    def on_edit(self):
        idx = self.view.currentIndex()
        if not idx.isValid():
            QMessageBox.information(self, "Select", "Please select a row to edit")
            return
        new_text = self.input.text().strip()
        if not new_text:
            QMessageBox.information(self, "Empty", "Please enter replacement text")
            return
        row = idx.row()
        cmd = EditCommand(self.model, row, new_text, description=f"Edit row {row+1}")
        self.undo_stack.push(cmd)
        self.input.clear()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = MainWindow()
    widget.show()
    sys.exit(app.exec())
