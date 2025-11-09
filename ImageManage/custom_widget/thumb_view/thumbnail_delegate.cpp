// #include "thumbnail_delegate.h"
// #include "thumbnail_model.h"
// #include <QPainter>
// #include <QApplication>
// #include <QMouseEvent>
// #include <QDebug>

// ThumbnailDelegate::ThumbnailDelegate(QObject *parent)
//     : QStyledItemDelegate(parent), m_thumb_size(120)  {

// }

// QRect ThumbnailDelegate::thumbnailRect(const QStyleOptionViewItem &option) const {
//   // leave some padding
//   const int pad = 6;
//   QRect r = option.rect.adjusted(pad, pad, -pad, -pad);
//   // keep square area for thumbnail
//   int side = qMin(r.width(), r.height());
//   QRect thumbRect(r.x(), r.y() + (r.height() - side) / 2, side, side);
//   return thumbRect;
// }

// QRect ThumbnailDelegate::deleteButtonRect(const QStyleOptionViewItem &option) const
// {
//   QRect thumb = thumbnailRect(option);
//   const int btnSize = qMax(16, thumb.width() / 6); // scale button with thumb
//   // place at top-right of thumbnail
//   QPoint topRight = thumb.topRight();
//   QRect btnRect(topRight.x() - btnSize + 1, topRight.y() + 1, btnSize, btnSize);
//   return btnRect;
// }

// void ThumbnailDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
//                               const QModelIndex &index) const {
//   painter->save();

//   // selection/focus background
//   QStyleOptionViewItem opt = option;
//   initStyleOption(&opt, index);
//   opt.text.clear();
//   opt.icon = QIcon(); // we draw manually
//   QApplication::style()->drawControl(QStyle::CE_ItemViewItem, &opt, painter);

//   QRect r = option.rect;
//   // compute pix rect: right side
//   int pad = 6;
//   int pixW = m_thumb_size;
//   int pixH = m_thumb_size;
//   // keep inside rect
//   pixW = qMin(pixW, r.width() - 2*pad);
//   pixH = qMin(pixH, r.height() - 2*pad);

//   QRect pixRect(r.left() + (r.width() - pixW) / 2, r.top() + (r.height() - pixH) / 2, pixW, pixH);

//   QVariant v = index.data(Qt::DecorationRole);
//   if (v.canConvert<QPixmap>()) {
//     QPixmap pm = qvariant_cast<QPixmap>(v);
//     QPixmap scaled = pm.scaled(pixRect.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
//     // center scaled inside pixRect
//     QPoint center = pixRect.center() - QPoint(scaled.width()/2, scaled.height()/2);
//     painter->drawPixmap(center, scaled);
//   } else {
//     // placeholder
//     painter->fillRect(pixRect, QColor(220,220,220));
//     painter->drawRect(pixRect);
//   }

//   // draw label (index number) at top-left small
//   QString name = index.data(Qt::DisplayRole).toString();
//   QString numLabel = QString::number(index.row()+1) + (name.isEmpty() ? "" : (": " + name));
//   QRect textR = r.adjusted(4, 4, -4, -4);
//   painter->setPen(Qt::black);
//   painter->drawText(textR, Qt::AlignLeft | Qt::AlignTop, numLabel);

//   painter->restore();
// }

// QSize ThumbnailDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
// {
//   // // let the height be driven by the view's iconSize if available via DecorationRole
//   // // fallback to 128
//   // QSize s = QSize(140, 160);
//   // // If model has Pixmap, try to get its size
//   // QVariant dec = index.data(Qt::DecorationRole);
//   // if (dec.canConvert<QPixmap>()) {
//   //   QPixmap px = dec.value<QPixmap>();
//   //   int h = px.height() + 40; // extra for filename
//   //   int w = px.width() + 20;
//   //   s = QSize(w, h);
//   // }
//   // return s;
//   int w = m_thumb_size + 12; // padding
//   int h = m_thumb_size + 12;
//   return QSize(w, h);
// }

// bool ThumbnailDelegate::editorEvent(QEvent *event, QAbstractItemModel *model,
//                                     const QStyleOptionViewItem &option, const QModelIndex &index)
// {
//   if (!index.isValid()) return false;

//   if (event->type() == QEvent::MouseButtonRelease) {
//     QMouseEvent *me = static_cast<QMouseEvent*>(event);
//     QRect btnR = deleteButtonRect(option);
//     if (btnR.contains(me->pos())) {
//       // emit signal that this index should be removed
//       emit removeRequested(index);
//       return true; // handled
//     }
//   }
//   return QStyledItemDelegate::editorEvent(event, model, option, index);
// }
