#include <QApplication>
#include "../include/hw4_package/main_window.hpp"
#include "../include/hw4_package/qnode.hpp"

int main(int argc, char* argv[])
{
  QApplication a(argc, argv);

  QNode qnode(argc, argv);
  qnode.init();

  MainWindow w(&qnode);
  w.show();

  int result = a.exec();

  return result;
}
