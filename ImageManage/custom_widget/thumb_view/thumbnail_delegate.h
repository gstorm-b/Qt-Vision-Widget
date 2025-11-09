#ifndef THUMBNAIL_DELEGATE_H
#define THUMBNAIL_DELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QApplication>
#include <QAbstractItemView>
#include "custom_widget/thumb_view/thumbnail_model.h"

class ThumbnailDelegate : public QStyledItemDelegate {
  Q_OBJECT
public:
  explicit ThumbnailDelegate(QObject *parent = nullptr)
      : QStyledItemDelegate(parent) {}

  // Paint the title (index + name) on top and thumbnail centered below.
  void paint(QPainter *painter,
             const QStyleOptionViewItem &option,
             const QModelIndex &index) const override
  {
    painter->save();

    // Draw background & selection
    QStyleOptionViewItem opt = option;
    initStyleOption(&opt, index);
    const QWidget *widget = option.widget;
    QStyle *style = widget ? widget->style() : QApplication::style();
    style->drawPrimitive(QStyle::PE_PanelItemViewItem, &opt, painter, widget);

    const int padding = 6;
    const int titleHeight = 22;
    QRect rect = option.rect;

    // Title text
    QString name = index.data(Qt::DisplayRole).toString();
    int row = index.row() + 1;
    QString title = QString("%1. %2").arg(row).arg(name);
    QRect titleRect(rect.x() + padding, rect.y(), rect.width() - 2*padding, titleHeight);

    QFont titleFont = option.font;
    titleFont.setBold(true);
    painter->setFont(titleFont);
    QColor textColor = (option.state & QStyle::State_Selected) ? option.palette.highlightedText().color()
                                                               : option.palette.text().color();
    painter->setPen(textColor);
    painter->drawText(titleRect, Qt::AlignLeft | Qt::AlignVCenter, title);

    // Thumbnail area
    QRect thumbArea(rect.x() + padding, rect.y() + titleHeight + padding,
                    rect.width() - 2*padding, rect.height() - titleHeight - 2*padding);

    QVariant pixVar = index.data(ThumbnailModel::PixmapRole);
    QPixmap pix = pixVar.value<QPixmap>();
    if (!pix.isNull()) {
      QSize targetSize = pix.size();
      targetSize.scale(thumbArea.size(), Qt::KeepAspectRatio);
      QPoint topLeft(thumbArea.x() + (thumbArea.width() - targetSize.width())/2,
                     thumbArea.y() + (thumbArea.height() - targetSize.height())/2);
      QRect drawRect(topLeft, targetSize);
      painter->drawPixmap(drawRect, pix);
    } else {
      painter->setPen(option.palette.mid().color());
      painter->drawRect(thumbArea);
      painter->drawText(thumbArea, Qt::AlignCenter, QObject::tr("No Image"));
    }

    painter->restore();
  }

  // sizeHint: make item height equal to view's viewport height (so items fill vertical space),
  // width is based on a ratio so thumbnails look good.
  QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override {
    Q_UNUSED(index);
    const QWidget *w = option.widget;
    int viewHeight = 120; // fallback
    if (w) {
      if (const QAbstractItemView *v = qobject_cast<const QAbstractItemView*>(w)) {
        viewHeight = v->viewport()->height();
      } else {
        viewHeight = w->height();
      }
    }
    // ensure minimum height
    viewHeight = qMax(viewHeight, 80);
    // choose width proportional to height (you can tweak the ratio)
    int width = qMax(100, viewHeight * 3 / 4);
    return QSize(width, viewHeight);
  }
};

#endif // THUMBNAIL_DELEGATE_H
