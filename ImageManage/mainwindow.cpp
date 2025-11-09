#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "custom_widget/thumb_view/thumbnail_model.h"

MainWindow::MainWindow(
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

  ui->setupUi(this);

  m_model = new ThumbnailModel(this);
  ui->listview_image->setModel(m_model);

  connect(ui->btn_add, &QPushButton::clicked,
          this, &MainWindow::btn_add_clicked);
  connect(ui->btn_delete, &QPushButton::clicked,
          this, &MainWindow::btn_delete_clicked);

  auto_increase = 0;
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::btn_add_clicked() {
  ui->image_view->loadImage(load_path);
  // m_model->addImage(load_path);
  // ui->listview_image->addImage(load_path);
  QPixmap pix = QPixmap(load_path);
  QString name = QString("Image %1").arg(auto_increase++);
  ui->listview_image->addItem(ThumbnailItem(pix, name, load_path));
}

void MainWindow::btn_delete_clicked() {
  ui->image_view->removeImage();
}
