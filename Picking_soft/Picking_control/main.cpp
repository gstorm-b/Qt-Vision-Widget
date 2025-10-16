#include "mainwindow.h"

#include <QApplication>
#include <QFile>

#include "form/job/dialog_job_select.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // load qss
  QFile styleSheetFile(":/style_sheet/style/main_style.qss");
  styleSheetFile.open(QFile::ReadOnly);
  QString styleSheet = QLatin1String(styleSheetFile.readAll());
  a.setStyleSheet(styleSheet);

  DialogJobSelect form_job;
  form_job.show();
  form_job.exec();

  MainWindow w;
  w.show();
  return a.exec();
}
