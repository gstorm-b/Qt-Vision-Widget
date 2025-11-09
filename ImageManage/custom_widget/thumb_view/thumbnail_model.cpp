#include "thumbnail_model.h"
#include <QIODevice>
#include <QByteArray>
#include <QDataStream>
#include <QStringLiteral>

ThumbnailModel::ThumbnailModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int ThumbnailModel::rowCount(const QModelIndex &parent) const {
  Q_UNUSED(parent);
  return static_cast<int>(m_items.size());
}

QVariant ThumbnailModel::data(const QModelIndex &index, int role) const {
  if (!index.isValid() || index.row() < 0 || index.row() >= rowCount())
    return {};
  const ThumbnailItem &it = m_items.at(index.row());
  switch (role) {
    case Qt::DisplayRole:
    case NameRole:
      return it.name;
    case PixmapRole:
      return it.pixmap;
    case PathRole:
      return it.path;
    default:
      return {};
  }
}

QHash<int, QByteArray> ThumbnailModel::roleNames() const {
  QHash<int, QByteArray> roles;
  roles[PixmapRole] = "pixmap";
  roles[NameRole] = "name";
  roles[PathRole] = "path";
  return roles;
}

Qt::ItemFlags ThumbnailModel::flags(const QModelIndex &index) const {
  // Allow drop on items as well as drag from items
  if (!index.isValid()) {
    // root: accept drops too
    return Qt::ItemIsDropEnabled;
  }
  return Qt::ItemIsSelectable | Qt::ItemIsEnabled |
         Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

// --- Drag & Drop support ---
// Use a custom mime type to encode the source row(s).
QStringList ThumbnailModel::mimeTypes() const {
  return { QStringLiteral("application/vnd.thumbnail.list") };
}

QMimeData *ThumbnailModel::mimeData(const QModelIndexList &indexes) const {
  if (indexes.isEmpty()) return nullptr;

  // Encode list of rows (support multi selection)
  QByteArray encoded;
  QDataStream stream(&encoded, QIODevice::WriteOnly);
  QList<int> rows;
  for (const QModelIndex &idx : indexes) {
    if (idx.isValid())
      rows.append(idx.row());
  }
  // ensure rows sorted ascending (important when removing)
  std::sort(rows.begin(), rows.end());
  stream << rows;

  QMimeData *mime = new QMimeData();
  mime->setData(QStringLiteral("application/vnd.thumbnail.list"), encoded);
  return mime;
}

bool ThumbnailModel::dropMimeData(const QMimeData *data, Qt::DropAction action,
                                  int row, int column, const QModelIndex &parent) {
  Q_UNUSED(column);
  Q_UNUSED(parent);
  if (!data || action == Qt::IgnoreAction) return false;
  if (!data->hasFormat(QStringLiteral("application/vnd.thumbnail.list")))
    return false;

  QByteArray encoded = data->data(QStringLiteral("application/vnd.thumbnail.list"));
  QDataStream stream(&encoded, QIODevice::ReadOnly);
  QList<int> srcRows;
  stream >> srcRows;
  if (srcRows.isEmpty()) return false;

  // target row: if -1 (drop at end) set to end
  int destRow = row;
  if (destRow == -1) destRow = rowCount();

  // We will remove the items from the model and then insert them at destRow (after adjustment).
  // To preserve relative order when moving multiple selected items, handle carefully.

  // Convert srcRows to QVector<int> and ensure ascending unique
  std::vector<int> src;
  for (int r : srcRows) src.push_back(r);
  std::sort(src.begin(), src.end());
  src.erase(std::unique(src.begin(), src.end()), src.end());

  // If destination is inside the block being moved, we treat as no-op
  // Compute lowest src and highest src
  int srcFirst = src.front();
  int srcLast = src.back();

  // If destRow points to position after removal, we may need to adjust destRow when removing items that come before it.
  // We'll remove from highest to lowest to avoid index shift problems.
  // But first determine final insertion position relative to items AFTER removal.
  // Count how many source rows are < destRow to compute adjustedDest
  int countBeforeDest = 0;
  for (int r : src) if (r < destRow) ++countBeforeDest;
  int adjustedDest = destRow - countBeforeDest; // position in array after removals where we insert

  // Extract moving items
  std::vector<ThumbnailItem> moving;
  moving.reserve(src.size());
  // Remove items from highest to lowest
  for (auto it = src.rbegin(); it != src.rend(); ++it) {
    int r = *it;
    if (r < 0 || r >= rowCount()) continue;
    beginRemoveRows(QModelIndex(), r, r);
    moving.push_back(m_items[r]); // push_back in reverse order; we'll reverse later
    m_items.erase(m_items.begin() + r);
    endRemoveRows();
  }
  // moving currently contains items in reverse order, restore correct order
  std::reverse(moving.begin(), moving.end());

  // Insert moving items at adjustedDest (they will be inserted in order)
  int insertPos = adjustedDest;
  for (size_t i = 0; i < moving.size(); ++i) {
    beginInsertRows(QModelIndex(), insertPos + static_cast<int>(i), insertPos + static_cast<int>(i));
    m_items.insert(m_items.begin() + insertPos + static_cast<int>(i), moving[i]);
    endInsertRows();
  }

  return true;
}

Qt::DropActions ThumbnailModel::supportedDropActions() const {
  return Qt::MoveAction;
}

bool ThumbnailModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                              const QModelIndex &destinationParent, int destinationChild) {
  Q_UNUSED(sourceParent);
  Q_UNUSED(destinationParent);

  if (count <= 0 || sourceRow < 0 || sourceRow + count > rowCount())
    return false;

  // destinationChild is the row **after** which the block will be inserted
  // Qt's beginMoveRows expects destinationChild to be the index in the destination BEFORE insertion.
  // If moving down within same model, be careful with indices.
  int dest = destinationChild;
  if (dest < 0) dest = rowCount(); // append

  // If no-op (source == dest or moving to same place)
  if (sourceRow == dest || sourceRow + count == dest)
    return false;

  beginMoveRows(QModelIndex(), sourceRow, sourceRow + count - 1, QModelIndex(), dest);
  // perform move in vector
  std::vector<ThumbnailItem> newItems;
  newItems.reserve(m_items.size());
  // 1) copy all items except the moving block
  for (int i = 0; i < sourceRow; ++i)
    newItems.push_back(m_items[i]);
  // will insert block later; keep pointer to moving block
  std::vector<ThumbnailItem> moving;
  for (int i = sourceRow; i < sourceRow + count; ++i)
    moving.push_back(m_items[i]);
  // remaining items after moving block
  for (int i = sourceRow + count; i < (int)m_items.size(); ++i)
    newItems.push_back(m_items[i]);

  // insert moving block at destPos in newItems
  int destPos = dest;
  // when sourceRow < dest, after removing block, the indexes shift left, so dest decreases by count
  if (sourceRow < dest) destPos = dest - count;
  if (destPos < 0) destPos = 0;
  if (destPos > (int)newItems.size()) destPos = (int)newItems.size();

  std::vector<ThumbnailItem> result;
  result.reserve(m_items.size());
  // items before destPos
  for (int i = 0; i < destPos; ++i)
    result.push_back(newItems[i]);
  // insert moving block
  for (auto &it : moving) result.push_back(it);
  // rest
  for (int i = destPos; i < (int)newItems.size(); ++i)
    result.push_back(newItems[i]);

  m_items.swap(result);
  endMoveRows();
  return true;
}

// --- model API ---
void ThumbnailModel::addItem(const ThumbnailItem &item) {
  beginInsertRows(QModelIndex(), rowCount(), rowCount());
  m_items.push_back(item);
  endInsertRows();
}

void ThumbnailModel::insertItem(int pos, const ThumbnailItem &item) {
  if (pos < 0) pos = 0;
  if (pos > rowCount()) pos = rowCount();
  beginInsertRows(QModelIndex(), pos, pos);
  m_items.insert(m_items.begin() + pos, item);
  endInsertRows();
}

void ThumbnailModel::removeAt(int row) {
  if (row < 0 || row >= rowCount()) return;
  beginRemoveRows(QModelIndex(), row, row);
  m_items.erase(m_items.begin() + row);
  endRemoveRows();
}

void ThumbnailModel::clear() {
  beginResetModel();
  m_items.clear();
  endResetModel();
}

ThumbnailItem ThumbnailModel::itemAt(int row) const {
  if (row < 0 || row >= rowCount()) return {};
  return m_items.at(row);
}
