#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QToolButton>


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

  void tbtn_navigate_clicked();

private:
  Ui::MainWindow *ui;
  QMap<QObject*, QWidget*> widget_list;
};
#endif // MAINWINDOW_H
