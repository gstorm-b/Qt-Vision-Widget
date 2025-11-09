#include "thumbnail_list_view.h"
#include <QDebug>
#include <QItemSelectionModel>

ThumbnailListView::ThumbnailListView(QWidget *parent)
    : QListView(parent),
    m_model(new ThumbnailModel(this)),
    m_delegate(new ThumbnailDelegate(this))
{
  setModel(m_model);
  setItemDelegate(m_delegate);

  // Show horizontally
  setViewMode(QListView::IconMode);
  setFlow(QListView::LeftToRight);
  setWrapping(true); // no wrap, scroll horizontally
  setResizeMode(QListView::Adjust);
  setSpacing(8);
  setSelectionMode(QAbstractItemView::SingleSelection);
  setUniformItemSizes(true);

  // Drag & drop for reordering
  setDragEnabled(true);
  setAcceptDrops(true);
  setDropIndicatorShown(true);
  setDefaultDropAction(Qt::MoveAction);
  setDragDropMode(QAbstractItemView::InternalMove);

  ensureSelectionConnection();
}

void ThumbnailListView::ensureSelectionConnection() {
  // connect selection change -> emit itemSelected
  if (selectionModel()) {
    // disconnect previous to avoid multiple connections
    disconnect(selectionModel(), &QItemSelectionModel::currentChanged, this, &ThumbnailListView::onCurrentChanged);
    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &ThumbnailListView::onCurrentChanged);
  }
}

void ThumbnailListView::addItem(const ThumbnailItem &item) {
  if (!m_model) return;
  m_model->addItem(item);
  updateGeometries();
}

void ThumbnailListView::insertItem(int pos, const ThumbnailItem &item) {
  if (!m_model) return;
  m_model->insertItem(pos, item);
  updateGeometries();
}

void ThumbnailListView::removeAt(int row) {
  if (!m_model) return;
  m_model->removeAt(row);
}

ThumbnailItem ThumbnailListView::itemAt(int row) const {
  if (!m_model) return {};
  return m_model->itemAt(row);
}

void ThumbnailListView::onCurrentChanged(const QModelIndex &current, const QModelIndex &previous) {
  Q_UNUSED(previous);
  if (!current.isValid()) return;
  if (m_model) {
    ThumbnailItem it = m_model->itemAt(current.row());
    emit itemSelected(current.row(), it);
  }
}

void ThumbnailListView::setModel(ThumbnailModel *model) {
  QListView::setModel(model);
  ThumbnailModel *m = model;
  if (m) m_model = m;
  ensureSelectionConnection();
}
