// #include "thumbnail_item_widget.h"
// #include <QLabel>
// #include <QPushButton>
// #include <QHBoxLayout>
// #include <QVBoxLayout>
// #include <QPainter>
// #include <QStyle>
// #include <QStackedLayout>

// ThumbnailItemWidget::ThumbnailItemWidget(const QString &filePath, QWidget *parent)
//     : QWidget(parent),
//     m_filePath(filePath),
//     m_thumbLabel(new QLabel(this)),
//     m_nameLabel(new QLabel(this)),
//     m_deleteBtn(new QPushButton("✕", this)),
//     m_thumbArea(128,128) {
//   m_thumbLabel->setFixedSize(m_thumbArea);
//   m_thumbLabel->setAlignment(Qt::AlignCenter);
//   m_thumbLabel->setStyleSheet("background: #eaeaea; border: 1px solid #ccc;");

//   m_nameLabel->setText(filePath.section('/', -1)); // filename
//   m_nameLabel->setAlignment(Qt::AlignCenter);
//   m_nameLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

//   m_deleteBtn->setFixedSize(22,22);
//   m_deleteBtn->setToolTip("Remove");
//   m_deleteBtn->setFocusPolicy(Qt::NoFocus);
//   m_deleteBtn->setStyleSheet("QPushButton { border-radius:11px; background: rgba(200,50,50,0.9); color: white; }");

//   // layout: thumbnail over filename, delete button overlay on top-right
//   QVBoxLayout *v = new QVBoxLayout;
//   v->setContentsMargins(6,6,6,6);
//   v->setSpacing(4);

//   // container for thumb + delete overlay
//   QWidget *thumbContainer = new QWidget(this);
//   thumbContainer->setFixedSize(m_thumbArea.width()+2, m_thumbArea.height()+2);
//   QStackedLayout *stack = new QStackedLayout(thumbContainer);
//   QWidget *thumbWidget = new QWidget(thumbContainer);
//   QHBoxLayout *thumbLayout = new QHBoxLayout(thumbWidget);
//   thumbLayout->setContentsMargins(0,0,0,0);
//   thumbLayout->addWidget(m_thumbLabel, 0, Qt::AlignCenter);
//   stack->addWidget(thumbWidget);

//   // place delete button absolute using layout on the main layout
//   QHBoxLayout *topRow = new QHBoxLayout;
//   topRow->setContentsMargins(0,0,0,0);
//   topRow->addStretch();
//   topRow->addWidget(m_deleteBtn);
//   topRow->setAlignment(m_deleteBtn, Qt::AlignTop | Qt::AlignRight);

//   v->addLayout(topRow);
//   v->addWidget(thumbContainer, 0, Qt::AlignCenter);
//   v->addWidget(m_nameLabel);

//   setLayout(v);

//   connect(m_deleteBtn, &QPushButton::clicked, this, [this](){
//     emit removeRequested(m_filePath);
//   });
// }

// void ThumbnailItemWidget::setThumbnail(const QPixmap &pix)
// {
//   if (pix.isNull()) {
//     // placeholder: draw gray
//     QPixmap p(m_thumbArea);
//     p.fill(QColor("#eaeaea"));
//     m_thumbLabel->setPixmap(p);
//     return;
//   }
//   QPixmap scaled = pix.scaled(m_thumbArea, Qt::KeepAspectRatio, Qt::SmoothTransformation);
//   m_thumbLabel->setPixmap(scaled);
// }

// void ThumbnailItemWidget::setThumbSize(const QSize &size)
// {
//   // keep square area
//   int side = qMin(size.width(), size.height());
//   m_thumbArea = QSize(side, side);
//   m_thumbLabel->setFixedSize(m_thumbArea);
//   // update container size heuristics
//   updateGeometry();
// }

// QString ThumbnailItemWidget::filePath() const { return m_filePath; }
