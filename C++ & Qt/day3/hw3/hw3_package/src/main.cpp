#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QBrush>
#include <QVBoxLayout>
#include <QApplication>

#include <QVBoxLayout>
#include "../include/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MyWidget *myWidget = new MyWidget();
    myWidget->setMinimumSize(600, 600);
    myWidget->show();


    return app.exec();
}
