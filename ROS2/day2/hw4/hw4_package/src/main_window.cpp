#include "../include/hw4_package/main_window.hpp"
#include <QPainter>
#include <cmath> 

MainWindow::MainWindow(QNode* qnode, QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindowDesign)
  , qnode_(qnode)
{
   ui->setupUi(this);


   connect(qnode_, &QNode::jointStateReceived,
           this, &MainWindow::updateJointAngles);
   connect(qnode_, &QNode::commandReceived,
           this, &MainWindow::updateJointAngle);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.translate(300, 300); 
    painter.rotate(angle1);
    painter.drawLine(0, 0, 100, 0);  

    painter.translate(100, 0);  
    painter.rotate(angle2);
    painter.drawLine(0, 0, 80, 0);   

    painter.translate(80, 0);  
    painter.rotate(angle3);
    painter.drawLine(0, 0, 60, 0);  

    painter.restore();
}

void MainWindow::updateJointAngle(const QString& name, int angle)
{
    if (name == "joint1")
    {
        angle1 = qBound(0, angle, 360);
    }
    else if (name == "joint2")
    {
        angle2 = qBound(0, angle, 360);
    }
    else if (name == "joint3")
    {
        angle3 = qBound(0, angle, 360);
    }
    update();
}
