#include "dialog_job_select.h"
#include "ui_dialog_job_select.h"

#include <QStyle>
#include <QToolButton>
#include <QIcon>
#include <QSize>
#include <QtSvg>

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
  ui->tbtn_load_last_job->setContentsMargins(10, 10, 10, 10);

  ui->tbtn_new_job->setText("Create New Job");
  ui->tbtn_load_job->setText("Load Job");
  ui->tbtn_load_last_job->setText("Load Last Job");

  ui->tbtn_new_job->setMinimumSize(150, 150);
  ui->tbtn_load_job->setMinimumSize(150, 150);
  ui->tbtn_load_last_job->setMinimumSize(150, 150);

  ui->tbtn_new_job->setMaximumSize(200, 200);
  ui->tbtn_load_job->setMaximumSize(200, 200);
  ui->tbtn_load_last_job->setMaximumSize(200, 200);

  // ui->tbtn_load_job->setCheckable(true);
  // QIcon set_job_icon;
  // set_job_icon.addFile(QStringLiteral(":/icon/icon/new-file-icon.svg"),
  //              QSize(), QIcon::Normal, QIcon::On);
  // set_job_icon.addFile(QStringLiteral(":/icon/icon/new-file-icon-dark.svg"),
  //              QSize(), QIcon::Active, QIcon::On);
  //

  ui->tbtn_new_job->setIconSize(QSize(100,100));
  ui->tbtn_load_job->setIconSize(QSize(100,100));
  ui->tbtn_load_last_job->setIconSize(QSize(100,100));

  ui->tbtn_new_job->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_load_job->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
  ui->tbtn_load_last_job->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  ui->tbtn_load_job->setNormalIcon(QIcon(":/icon/icon/new-file-icon.svg"));
  // ui->tbtn_load_job->setHoverIcon(QIcon(":/icon/icon/new-file-icon-dark.svg"));
  ui->tbtn_load_job->setPressedIcon(QIcon(":/icon/icon/new-file-icon-dark.svg"));
  // ui->tbtn_load_job->setCheckedIcon(QIcon(":/icon/icon/new-file-icon-dark.svg"));

  // ui->tbtn_new_job->setIcon(QIcon(":/icon/icon/plus-square-icon.svg"));
  // ui->tbtn_load_job->setIcon(QIcon(":/icon/icon/new-file-icon.svg"));
  // ui->tbtn_load_last_job->setIcon(QIcon(":/icon/icon/new-file-icon.svg"));

  // ui->tbtn_new_job->setStyleSheet(tool_button_style);
  // ui->tbtn_load_job->setStyleSheet(tool_button_style);
  // ui->tbtn_load_last_job->setStyleSheet(tool_button_style);
}
