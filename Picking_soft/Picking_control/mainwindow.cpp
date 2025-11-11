#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "form/robot/moveleditor.h"
#include "custom_widget/robot/commandeditor.h"
#include "custom_widget/image_widget.h"
#include "custom_widget/dialog_set_new_pattern.h"

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
  ui->tbtn_vision->setIcon(QIcon(":/icon/icon/plc-icon.svg"));
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

  widget_list.insert(ui->tbtn_dashboard, ui->page_dashboard);
  widget_list.insert(ui->tbtn_vision, ui->page_vision);
  widget_list.insert(ui->tbtn_robot, ui->page_robot);

  ui->tbtn_dashboard->setCheckable(true);
  ui->tbtn_vision->setCheckable(true);
  ui->tbtn_robot->setCheckable(true);

  ui->tbtn_dashboard->setChecked(true);
  ui->tbtn_vision->setChecked(false);
  ui->tbtn_robot->setChecked(false);

  ui->stackedWidget->setCurrentWidget(ui->page_dashboard);

  ui->treeView->registerCommandType("MoveL", []{ return std::make_shared<rp::HyMoveLCommand>(); });
  ui->treeView->registerCommandType("If",    []{ return std::make_shared<rp::HyIfCommand>(); });

  command_list_model = ui->treeView->model();

  rp::EditorRegistry::registerEditor("MoveL", [](QWidget* p){ return new rp::MoveLEditor(p); });

  connect(ui->btn_move_up, &QPushButton::clicked,
          this, &MainWindow::btn_move_up_clicked);
  connect(ui->btn_move_down, &QPushButton::clicked,
          this, &MainWindow::btn_move_down_clicked);
  connect(ui->treeView, &rp::CommandTreeView::commandClicked,
          this, &MainWindow::CommandClicked);

  QString path = "image_6.bmp";
  QPixmap pixmap(path);
  qDebug() << "Is image null:" << pixmap.isNull();
  ui->graphicsView_main->loadImage(pixmap);
  // ui->graphicsView_main->

  connect(ui->btn_set_roi, &QPushButton::clicked,
          this, &MainWindow::btn_set_roi_clicked);
  connect(ui->btn_set_polygon, &QPushButton::clicked,
          this, &MainWindow::btn_set_polygon_clicked);
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

void MainWindow::btn_move_up_clicked() {
  command_list_model->moveUp(ui->treeView->currentIndex());
}

void MainWindow::btn_move_down_clicked() {
  command_list_model->moveDown(ui->treeView->currentIndex());
}

void MainWindow::CommandClicked(rp::Command* cmd) {
  ui->stackedWidget_cmd_editor->editCommand(ui->treeView->model(), cmd);
}

void MainWindow::btn_set_roi_clicked() {
  ui->graphicsView_main->startDrawROI(ImageWidget::RotatedROI);
}

void MainWindow::btn_set_polygon_clicked() {
  DialogSetNewPattern new_pattern_set;
  new_pattern_set.exec();
}
