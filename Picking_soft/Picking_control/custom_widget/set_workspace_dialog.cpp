#include "set_workspace_dialog.h"
#include "ui_set_workspace_dialog.h"

SetWorkspaceDialog::SetWorkspaceDialog(
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SetWorkspaceDialog) {
  ui->setupUi(this);
}

SetWorkspaceDialog::~SetWorkspaceDialog() {
  delete ui;
}
