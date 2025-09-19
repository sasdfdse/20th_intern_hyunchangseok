#include <QApplication>
#include <QVBoxLayout>
#include "../include/mainwindow.h"
#include "ui_mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    QVBoxLayout *layout = new QVBoxLayout(&window);

    MyWidget *myWidget = new MyWidget();
    myWidget->setMinimumSize(600, 600);
    layout->addWidget(myWidget);
    window.show();

    return a.exec();
}
