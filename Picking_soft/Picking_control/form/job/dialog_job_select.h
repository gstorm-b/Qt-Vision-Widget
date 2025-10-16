#ifndef DIALOG_JOB_SELECT_H
#define DIALOG_JOB_SELECT_H

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
};

#endif // DIALOG_JOB_SELECT_H
