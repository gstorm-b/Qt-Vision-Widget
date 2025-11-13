#ifndef DIVIDER_BAR_H
#define DIVIDER_BAR_H

#include <QWidget>
#include <QColor>

class DividerBar : public QWidget
{
  Q_OBJECT
  Q_PROPERTY(QColor color READ color WRITE setColor)
  Q_PROPERTY(int thickness READ thickness WRITE setThickness)
  Q_PROPERTY(Qt::PenStyle penStyle READ penStyle WRITE setPenStyle)

public:
  explicit DividerBar(QWidget* parent = nullptr);

  QColor color() const { return m_color; }
  void setColor(const QColor& c);

  int thickness() const { return m_thickness; }
  void setThickness(int t);

  Qt::PenStyle penStyle() const { return m_penStyle; }
  void setPenStyle(Qt::PenStyle style);

protected:
  void paintEvent(QPaintEvent* event) override;
  QSize sizeHint() const override;

private:
  QColor m_color;
  int m_thickness;
  Qt::PenStyle m_penStyle;
};

#endif // DIVIDER_BAR_H
