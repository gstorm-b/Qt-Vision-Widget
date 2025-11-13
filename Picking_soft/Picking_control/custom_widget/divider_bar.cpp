#include "divider_bar.h"
#include <QPainter>
#include <QStyleOption>
#include <QPalette>

DividerBar::DividerBar(QWidget* parent)
    : QWidget(parent),
    m_color(Qt::transparent), // dùng palette nếu chưa set bằng QSS
    m_thickness(1),
    m_penStyle(Qt::SolidLine)
{
  setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  // Chiều cao gợi ý theo thickness
  setMinimumHeight(m_thickness);
}

void DividerBar::setColor(const QColor& c)
{
  if (m_color == c) return;
  m_color = c;
  update();
}

void DividerBar::setThickness(int t)
{
  if (t <= 0) t = 1;
  if (m_thickness == t) return;
  m_thickness = t;
  setMinimumHeight(m_thickness);
  updateGeometry();
  update();
}

void DividerBar::setPenStyle(Qt::PenStyle style)
{
  if (m_penStyle == style) return;
  m_penStyle = style;
  update();
}

void DividerBar::paintEvent(QPaintEvent* event)
{
  Q_UNUSED(event);

  QStyleOption opt;
  opt.initFrom(this);

  // Nếu chưa set qua QSS (m_color transparent), dùng palette để lấy màu “mid” hoặc “dark”
  QColor lineColor = m_color.isValid() && m_color.alpha() > 0
                         ? m_color
                         : opt.palette.color(QPalette::Mid);

  QPainter p(this);
  p.setRenderHint(QPainter::Antialiasing, false);
  QPen pen(lineColor, m_thickness, m_penStyle, Qt::FlatCap);
  p.setPen(pen);

  // Vẽ đường ngang giữa theo thickness
  const int y = height() / 2;
  p.drawLine(0, y, width(), y);
}

QSize DividerBar::sizeHint() const
{
  return QSize(100, m_thickness); // rộng tùy bố cục, cao theo thickness
}

// Divider {
//   qproperty-color: #C0C4CC;      /* màu đường */
//   qproperty-thickness: 2;        /* độ dày (px) */
//   /* có thể đổi kiểu nét bằng code, Qt chưa hỗ trợ set PenStyle trực tiếp qua QSS */
// }

// /* Hoặc đặt theo theme tối */
// QWidget[theme="dark"] Divider {
//   qproperty-color: #3A3A3A;
//   qproperty-thickness: 1;
// }
