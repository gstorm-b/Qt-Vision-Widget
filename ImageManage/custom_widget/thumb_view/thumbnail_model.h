#ifndef THUMBNAIL_MODEL_H
#define THUMBNAIL_MODEL_H

#include <vector>
#include <QPixmap>
#include <QString>
#include <QAbstractListModel>
#include <QMimeData>

struct ThumbnailItem {
  QPixmap pixmap;
  QString name;
  QString path; // có thể để trống

  ThumbnailItem() = default;
  ThumbnailItem(const QPixmap &p, const QString &n, const QString &pa = {})
      : pixmap(p), name(n), path(pa) {}
};

class ThumbnailModel : public QAbstractListModel {
  Q_OBJECT
public:
  enum Roles {
    PixmapRole = Qt::UserRole + 1,
    NameRole,
    PathRole
  };

  explicit ThumbnailModel(QObject *parent = nullptr);

  // core overrides
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QHash<int, QByteArray> roleNames() const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  // drag&drop support
  QStringList mimeTypes() const override;
  QMimeData *mimeData(const QModelIndexList &indexes) const override;
  bool dropMimeData(const QMimeData *data, Qt::DropAction action,
                    int row, int column, const QModelIndex &parent) override;
  Qt::DropActions supportedDropActions() const override;
  bool moveRows(const QModelIndex &sourceParent, int sourceRow, int count,
                const QModelIndex &destinationParent, int destinationChild) override;

  // API quản lý item
  void addItem(const ThumbnailItem &item);
  void insertItem(int pos, const ThumbnailItem &item);
  void removeAt(int row);
  void clear();
  ThumbnailItem itemAt(int row) const;

private:
  std::vector<ThumbnailItem> m_items;
};

#endif // THUMBNAIL_MODEL_H
