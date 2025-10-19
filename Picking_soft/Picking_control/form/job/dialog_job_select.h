#ifndef DIALOG_JOB_SELECT_H
#define DIALOG_JOB_SELECT_H

#include <QStringLiteral>
#include <QDialog>

namespace Ui { class DialogJobSelect; }

class DialogJobSelect : public QDialog {
  Q_OBJECT

public:
  explicit DialogJobSelect(QWidget *parent = nullptr);
  ~DialogJobSelect();

private:
  void init_form();

private:
  Ui::DialogJobSelect *ui;
  const QString tool_button_style = R"(
    QToolButton {
        qproperty-icon: url(:/icon/icon/new-file-icon-dark.svg);
        background-color: #3c3f41;
        color: white;
        border: 1px solid #2d2d2d;
        border-radius: 6px;
        padding: 15px;
    }
    QToolButton:hover {
        qproperty-icon: url(:/icon/icon/new-file-icon.svg);
        background-color: #505355;
        border: 1px solid #5c5c5c;
    }
    QToolButton:pressed {
        color: white;
        background-color: #dfcbd8;
        border: 1px solid #1e1e1e;
    }
    QToolButton:checked {
        background-color: #2a82da;
        border: 1px solid #1b4f91;
    }
    QToolButton:disabled {
        color: #777;
        background-color: #2a2a2a;
        border: 1px solid #222;
    }
)";

};

#endif // DIALOG_JOB_SELECT_H
