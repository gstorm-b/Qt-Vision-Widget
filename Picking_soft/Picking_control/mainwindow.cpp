#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
  ui->setupUi(this);

  init_main_screen();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::init_main_screen() {

  ui->tbtn_dashboard->setText(tr("Dashboard"));
  ui->tbtn_dashboard->setIcon(QIcon(":/icon/icon/dashboard-icon.svg"));
  ui->tbtn_dashboard->setIconSize(QSize(70,70));
  ui->tbtn_dashboard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  ui->tbtn_vision->setText(tr("Vision"));
  ui->tbtn_vision->setIcon(QIcon(":/icon/icon/vision-icon.svg"));
  ui->tbtn_vision->setIconSize(QSize(70,70));
  ui->tbtn_vision->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  ui->tbtn_robot->setText(tr("Robot"));
  ui->tbtn_robot->setIcon(QIcon(":/icon/icon/robot-icon.svg"));
  ui->tbtn_robot->setIconSize(QSize(70,70));
  ui->tbtn_robot->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  connect(ui->tbtn_dashboard, &TabWidgetButton::clicked,
          this, &MainWindow::tbtn_navigate_clicked);
  connect(ui->tbtn_vision, &TabWidgetButton::clicked,
          this, &MainWindow::tbtn_navigate_clicked);
  connect(ui->tbtn_robot, &TabWidgetButton::clicked,
          this, &MainWindow::tbtn_navigate_clicked);

  // widget_list.insert(ui->tbtn_dashboard->objectName(), ui->page);
  // widget_list.insert(ui->tbtn_vision->objectName(), ui->page_2);
  // widget_list.insert(ui->tbtn_robot->objectName(), ui->page_3);

  widget_list.insert(ui->tbtn_dashboard, ui->page);
  widget_list.insert(ui->tbtn_vision, ui->page_2);
  widget_list.insert(ui->tbtn_robot, ui->page_3);

  ui->tbtn_dashboard->setCheckable(true);
  ui->tbtn_vision->setCheckable(true);
  ui->tbtn_robot->setCheckable(true);

  ui->tbtn_dashboard->setChecked(true);
  ui->tbtn_vision->setChecked(false);
  ui->tbtn_robot->setChecked(false);

  ui->stackedWidget->setCurrentWidget(ui->page);
}

void MainWindow::tbtn_navigate_clicked() {
  // active widget
  QObject *sender_btn = sender();
  QWidget *wg = widget_list.value(sender_btn, nullptr);
  if (wg != nullptr) {
    ui->stackedWidget->setCurrentWidget(wg);
  }

  for (auto index = widget_list.cbegin(), end = widget_list.cend(); index != end; ++index) {
    TabWidgetButton* btn = qobject_cast<TabWidgetButton*>(index.key());
    btn->setChecked(btn == sender_btn);
  }
}

