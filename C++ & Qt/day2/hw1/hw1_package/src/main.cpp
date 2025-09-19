#include <QApplication>
#include <QSlider>
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

    QSlider *slider1 = new QSlider(Qt::Horizontal);
    slider1->setRange(0, 360);
    slider1->setValue(30);

    QSlider *slider2 = new QSlider(Qt::Horizontal);
  slider2->setRange(0, 360);
    slider2->setValue(45);

    QSlider *slider3 = new QSlider(Qt::Horizontal);
  slider3->setRange(0, 360);
    slider3->setValue(45);

    layout->addWidget(myWidget);
    layout->addWidget(slider1);
    layout->addWidget(slider2);
        layout->addWidget(slider3);

    QObject::connect(slider1, &QSlider::valueChanged, myWidget, &MyWidget::setAngle1);
    QObject::connect(slider2, &QSlider::valueChanged, myWidget, &MyWidget::setAngle2);
     QObject::connect(slider3, &QSlider::valueChanged, myWidget, &MyWidget::setAngle3);
    window.show();

    return a.exec();
}


