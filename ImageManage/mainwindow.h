#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "custom_widget/thumb_view/thumbnail_model.h"
#include "custom_widget/thumb_view/thumbnail_list_view.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void btn_add_clicked();
  void btn_delete_clicked();

private:
  Ui::MainWindow *ui;
  ThumbnailModel *m_model;
  QString load_path = "D:/Personal project/Vision/Qt-Vision-Widget/ImageManage/test_image_2.bmp";

  int auto_increase;
};
#endif // MAINWINDOW_H
