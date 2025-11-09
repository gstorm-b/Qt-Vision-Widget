#ifndef THUMBNAIL_LIST_VIEW_H
#define THUMBNAIL_LIST_VIEW_H

#include <QListView>
#include <QMap>
#include "thumbnail_model.h"
#include "thumbnail_delegate.h"

class ThumbnailListView : public QListView {
  Q_OBJECT
public:
  explicit ThumbnailListView(QWidget *parent = nullptr);

  // convenience API
  void addItem(const ThumbnailItem &item);
  void insertItem(int pos, const ThumbnailItem &item);
  void removeAt(int row);
  ThumbnailItem itemAt(int row) const;

  void setModel(ThumbnailModel *model);

signals:
  void itemSelected(int index, ThumbnailItem item);

private slots:
  void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
  void ensureSelectionConnection();

  ThumbnailModel *m_model = nullptr;
  ThumbnailDelegate *m_delegate = nullptr;
};

#endif // THUMBNAIL_LIST_VIEW_H
