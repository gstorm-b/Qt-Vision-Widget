#include "mainwindow.h"

#include <QApplication>
#include <QFile>

#include "form/job/dialog_job_select.h"

#define TURN_OFF_SELECT_JOB

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // load qss
  QFile styleSheetFile(":/style_sheet/style/main_style.qss");
  // QFile styleSheetFile(":/style_sheet/style/dracula_dark.qss");
  // QFile styleSheetFile(":/style_sheet/style/dracula_light.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);

#ifndef TURN_OFF_SELECT_JOB
  DialogJobSelect form_job;
  form_job.show();
  form_job.exec();
#endif

  MainWindow w;
  w.show();
  return a.exec();
}
