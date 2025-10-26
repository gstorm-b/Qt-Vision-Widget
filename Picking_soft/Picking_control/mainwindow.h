#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QToolButton>

#include "custom_widget/robot/commandmodel.h"
#include "form/robot/hyprgcommand.h"


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

  void btn_move_up_clicked();
  void btn_move_down_clicked();
  void CommandClicked(rp::Command* cmd);

  void btn_set_roi_clicked();
  void btn_set_polygon_clicked();

private:
  Ui::MainWindow *ui;
  QMap<QObject*, QWidget*> widget_list;
  rp::CommandModel *command_list_model;
};
#endif // MAINWINDOW_H
