#include "../include/mainwindow.h"
#include <QPainter>
#include <QtMath>
#include <QtGlobal>
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <iostream>

// QMainWindow를 상속
MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow), count(0)
{
    ui->setupUi(this);  // UI 초기화

    // 버튼 클릭 시 슬롯 연결
    connect(ui->pushButton, &QPushButton::clicked, this, &MyWidget::on_pushButton_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MyWidget::on_pushButton_2_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MyWidget::on_pushButton_3_clicked);

    connect(ui->pushButton_4, &QPushButton::clicked, this, &MyWidget::saveFile);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &MyWidget::loadFile);

    // QTimer 객체의 멤버 변수
    timer = new QTimer(this);
    timer->setInterval(40);  // 40ms마다
    connect(timer, &QTimer::timeout, this, &MyWidget::onTimerTimeout);
    timer->stop();

    timer1 = new QTimer(this);
        timer1->setInterval(40);
        connect(timer1, &QTimer::timeout, this, &MyWidget::onTimerTimeout1);
        timer1->stop();

    timer2 = new QTimer(this);
            timer2->setInterval(40);
            connect(timer2, &QTimer::timeout, this, &MyWidget::onTimerTimeout2);
            timer2->stop();

}

void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.translate(300, 300);  //팔1 시작점
    painter.rotate(angle1);
    painter.drawLine(0, 0, 100, 0);  // 팔 1

    painter.translate(100, 0);  // 팔 1끝으로 이동
    painter.rotate(angle2);
    painter.drawLine(0, 0, 80, 0);   // 팔 2

    painter.translate(80, 0);  // 팔 2끝으로 이동
    painter.rotate(angle3);
    painter.drawLine(0, 0, 60, 0);   // 팔 3

    painter.restore();
}

void MyWidget::setAngle1(int angle)
{
    angle1 = qBound(0, angle, 360);
    update();
}

void MyWidget::setAngle2(int angle)
{
    angle2 = qBound(0, angle, 360);
    update();
}

void MyWidget::setAngle3(int angle)
{
    angle3 = qBound(0, angle, 360);
    update();
}

// 버튼 클릭 시 호출되는 함수
void MyWidget::on_pushButton_clicked()
{
    count++;

    if (count % 4 == 2) {
        if (!timer->isActive()) {
            timer->start();  // 타이머 시작
        }
    }

    else if (count % 4 == 0) {
        if (timer->isActive()) {
            timer->stop();  // 타이머 정지
        }
    }

    else if (count>4&&count % 4 == 2) {
        if (!timer->isActive()) {
            timer->start();
        }
    }

    update();
}

void MyWidget::onTimerTimeout()
{

    if (count % 3 == 2) {
        angle1 -= 10;  // 반대 방향으로 회전
        direction1= 0;
    }
    else {
        angle1 += 10;  // 정방향으로 회전
        direction1= 1;
    }


    angle1 = qBound(0, angle1, 360);



    update();
}

void MyWidget::on_pushButton_2_clicked()
{
    count1++;

    if (count1 % 4 == 2) {
        if (!timer1->isActive()) {
            timer1->start();
        }
    }

    else if (count1 % 4 == 0) {
        if (timer1->isActive()) {
            timer1->stop();  // 타이머 정지
        }
    }

    else if (count1>4&&count1 % 4 == 2) {
        if (!timer1->isActive()) {
            timer1->start();  // 타이머 시작
        }
    }

    update();
}

void MyWidget::onTimerTimeout1()
{
    // count가 2일 때는 반대로 회전, 아니면 정상 방향으로 회전
    if (count1 % 3 == 2) {
        angle2 -= 10;  // 반대 방향으로 회전
        direction1= 0;
    }
    else {
        angle2 += 10;  // 정상 방향으로 회전
        direction1= 1;
    }

    angle2 = qBound(0, angle2, 360);



    update();
}

void MyWidget::on_pushButton_3_clicked()
{
    count2++;

    if (count2 % 4 == 2) {
        if (!timer2->isActive()) {
            timer2->start();  // 타이머 시작
        }
    }
    // 2번째 클릭 시 타이머 멈춤
    else if (count2 % 4 == 0) {
        if (timer2->isActive()) {
            timer2->stop();  // 타이머 정지
        }
    }

    else if (count2>4&&count2 % 4 == 2) {
        if (!timer2->isActive()) {
            timer2->start();  // 타이머 시작
        }
    }

    update();
}

void MyWidget::onTimerTimeout2()
{

    if (count2 % 3 == 2) {
        angle3 -= 10;
        direction1= 0;// 반대 방향으로 회전
    }
    else {
        angle3 += 10;
        direction1= 1;// 정방향으로 회전
    }


    angle3 = qBound(0, angle3, 360);



    update();
}

void MyWidget::saveFile()
{
    QFile file("arm_status.txt");  // 파일명 설정
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << "Angle1: " << angle1 << "\n";
        out << "Angle2: " << angle2 << "\n";
        out << "Angle3: " << angle3 << "\n";
        out << "Direction1: " << direction1 << "\n";  // 회전 방향
        out << "Direction2: " << direction2 << "\n";
        out << "Direction3: " << direction3 << "\n";
        file.close();
        std::cout << "State saved to arm_status.txt\n";
    }
    else {
        std::cout << "Error";
    }
}

//파일에서 불러오는 함수
void MyWidget::loadFile()
{
    QFile file("arm_status.txt");  // 파일명
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString line;

        // 파일에서 각도 및 방향 읽기
        while (!in.atEnd()) {
            line = in.readLine();
            if (line.startsWith("Angle1: ")) angle1 = line.mid(8).toInt();
            else if (line.startsWith("Angle2: ")) angle2 = line.mid(8).toInt();
             else if (line.startsWith("Angle3: ")) angle3 = line.mid(8).toInt();
            else if (line.startsWith("Direction1: ")) direction1 = line.mid(12).toInt();
            else if (line.startsWith("Direction2: ")) direction2 = line.mid(12).toInt();
            else if (line.startsWith("Direction3: ")) direction3 = line.mid(12).toInt();


     }
            setAngle1(angle1);
            setAngle2(angle2);
            setAngle3(angle3);


            if (direction1 == 1) {
                angle1 += 10;  // 시계방향
            }
            else {
                angle1 -= 10;  // 반시계방향
            }

            if (direction2 == 1) {
                angle2 += 10;
            }
            else {
                angle2 -= 10;
            }

            if (direction3 == 1) {
                angle3 += 10;
            }
            else {
                angle3 -= 10;
            }



    }

}

void MyWidget::on_pushButton_4_clicked()
{
    saveFile();
}


void MyWidget::on_pushButton_5_clicked()
{
    loadFile();
}

