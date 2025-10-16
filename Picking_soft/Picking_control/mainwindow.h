#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  void init_main_screen();

  void tbtn_dashboard_clicked();
  void tbtn_vision_clicked();
  void tbtn_robot_clicked();

private:
  Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
