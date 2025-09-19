#include "../include/mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPushButton>
#include <iostream>
#include <vector>

MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), count(0)
{
    ui->setupUi(this);  // UI 초기화


}

void MyWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setBrush(Qt::blue);
    painter.drawRect(rect());  // 전체 위젯을 파란색 사각형으로
}

void MyWidget::on_pushButton_clicked()
{   count ++;


    v.push_back(count);
    std::cout<<"빨래 넣기 성공! : "<< count << "번째 옷" << std::endl;

    update();
}

void MyWidget::on_pushButton_2_clicked()
{

    count --;

    if(count<0){ std::cout<<"꺼낼 빨래가 존재하지 않습니다! : "<< std::endl; exit(1);}
    v.pop_back();
        count_now = v.back();
    std::cout<<"빨래 꺼내기 성공! : "<< count << "벌 남음" <<  std::endl;
    std::cout<<"현재 : "<< count_now <<  std::endl;
    update();
}

