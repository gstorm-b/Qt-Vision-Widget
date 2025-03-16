#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(
    QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  connect(ui->btn_load_image, &QPushButton::clicked,
          this, &MainWindow::btn_load_image_clicked);
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::btn_load_image_clicked() {

  QString img_path = getImageFilePath(this);
  qDebug() << img_path;

  ui->image_view->loadImage(img_path);
}

QString MainWindow::getImageFilePath(QWidget *parent) {
  QSettings settings("YourCompany", "YourApp");
  QString lastDirectory = settings.value("lastDirectory", "").toString();

  QString filePath = QFileDialog::getOpenFileName(parent,
                                                  "Chọn ảnh",
                                                  lastDirectory,
                                                  "Image Files (*.png *.jpg *.jpeg *.bmp)");

  if (!filePath.isEmpty()) {
    QString directory = QFileInfo(filePath).absolutePath();
    settings.setValue("lastDirectory", directory);
  }

  return filePath;
}
