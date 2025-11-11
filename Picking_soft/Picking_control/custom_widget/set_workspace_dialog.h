#ifndef SET_WORKSPACE_DIALOG_H
#define SET_WORKSPACE_DIALOG_H

#include <QDialog>

namespace Ui { class SetWorkspaceDialog; }

class SetWorkspaceDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SetWorkspaceDialog(QWidget *parent = nullptr);
  ~SetWorkspaceDialog();

private:
  Ui::SetWorkspaceDialog *ui;
};

#endif // SET_WORKSPACE_DIALOG_H
