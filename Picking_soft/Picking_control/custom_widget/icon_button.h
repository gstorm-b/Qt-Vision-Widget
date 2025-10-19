#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <QToolButton>
#include <QIcon>
#include <QEvent>
#include <QEnterEvent>

class IconToolButton : public QToolButton {
  Q_OBJECT
public:
  explicit IconToolButton(QWidget *parent = nullptr)
      : QToolButton(parent) {

  }

  void setNormalIcon(const QIcon &icon) {
    m_normalIcon = icon;
    setIcon(m_normalIcon);
  }

  void setHoverIcon(const QIcon &icon) {
    m_hoverIcon = icon;
  }

  void setPressedIcon(const QIcon &icon) {
    m_pressedIcon = icon;
  }

  void setCheckedIcon(const QIcon &icon) {
    m_checkedIcon = icon;
  }

protected:
  // Hover enter
  void enterEvent(QEnterEvent *event) override {
    if (!isDown() && !isChecked() && !m_hoverIcon.isNull())
      setIcon(m_hoverIcon);
    QToolButton::enterEvent(event);
  }

  // Hover leave
  void leaveEvent(QEvent *event) override {
    if (!isDown() && !isChecked() && !m_normalIcon.isNull())
      setIcon(m_normalIcon);
    QToolButton::leaveEvent(event);
  }

  // Mouse pressed
  void mousePressEvent(QMouseEvent *event) override {
    if (!m_pressedIcon.isNull())
      setIcon(m_pressedIcon);
    QToolButton::mousePressEvent(event);
  }

  // Mouse released
  void mouseReleaseEvent(QMouseEvent *event) override {
    if (isChecked() && !m_checkedIcon.isNull())
      setIcon(m_checkedIcon);
    else if (underMouse() && !m_hoverIcon.isNull())
      setIcon(m_hoverIcon);
    else if (!m_normalIcon.isNull())
      setIcon(m_normalIcon);

    QToolButton::mouseReleaseEvent(event);
  }

  // Nếu button checkable, override toggle để set icon checked
  void nextCheckState() override {
    QToolButton::nextCheckState();
    if (isChecked() && !m_checkedIcon.isNull())
      setIcon(m_checkedIcon);
    else if (!m_normalIcon.isNull())
      setIcon(m_normalIcon);
  }

private:
  QIcon m_normalIcon;
  QIcon m_hoverIcon;
  QIcon m_pressedIcon;
  QIcon m_checkedIcon;
};

#endif // ICON_BUTTON_H
