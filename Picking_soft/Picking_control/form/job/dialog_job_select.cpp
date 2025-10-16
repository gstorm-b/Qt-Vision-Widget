#include "dialog_job_select.h"
#include "ui_dialog_job_select.h"

#include <QToolButton>
#include <QIcon>
#include <QSize>

DialogJobSelect::DialogJobSelect(
    QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogJobSelect) {
  ui->setupUi(this);

  this->setStyleSheet("QDialog { background-color: #474745; }");

  init_form();
}

DialogJobSelect::~DialogJobSelect() {
  delete ui;
}

void DialogJobSelect::init_form() {
  ui->tbtn_new_job->setContentsMargins(10, 10, 10, 10);
  ui->tbtn_load_job->setContentsMargins(10, 10, 10, 10);

  ui->tbtn_new_job->setText("Create New Job");
  ui->tbtn_load_job->setText("Load Job");

  ui->tbtn_new_job->setMinimumSize(150, 150);
  ui->tbtn_load_job->setMinimumSize(150, 150);

  ui->tbtn_new_job->setMaximumSize(200, 200);
  ui->tbtn_load_job->setMaximumSize(200, 200);

  ui->tbtn_new_job->setIcon(QIcon(":/icon/icon/add-icon.png"));
  ui->tbtn_load_job->setIcon(QIcon(":/icon/icon/load-icon.png"));

  ui->tbtn_new_job->setIconSize(QSize(100,100));
  ui->tbtn_load_job->setIconSize(QSize(100,100));

  ui->tbtn_new_job->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_load_job->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  ui->tbtn_new_job->setStyleSheet(R"(
    QToolButton {
        background-color: #3c3f41;
        color: white;
        border: 1px solid #2d2d2d;
        border-radius: 6px;
        padding: 15px;
    }
    QToolButton:hover {
        background-color: #505355;
        border: 1px solid #5c5c5c;
    }
    QToolButton:pressed {
        color: black;
        background-color: #c293b2;
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
)");

  ui->tbtn_load_job->setStyleSheet(R"(
    QToolButton {
        background-color: #3c3f41;
        color: white;
        border: 1px solid #2d2d2d;
        border-radius: 6px;
        padding: 15px;
    }
    QToolButton:hover {
        background-color: #505355;
        border: 1px solid #5c5c5c;
    }
    QToolButton:pressed {
        color: black;
        background-color: #c293b2;
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
)");
}
