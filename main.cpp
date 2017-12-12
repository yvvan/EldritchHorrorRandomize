#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
#if !defined(Q_OS_ANDROID) and !defined(Q_OS_IOS)
  QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
