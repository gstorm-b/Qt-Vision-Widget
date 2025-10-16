#ifndef TAB_WIDGET_BUTTON_H
#define TAB_WIDGET_BUTTON_H

#include <QToolButton>

class TabWidgetButton : public QToolButton {
  Q_OBJECT
public:
  TabWidgetButton(QWidget* parent = nullptr) :
      QToolButton(parent) {

  }

};

#endif // TAB_WIDGET_BUTTON_H
