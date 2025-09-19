#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QWidget>
#include "ui_mainwindow.h"

class MyWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

public slots:
    void setAngle1(int angle);
    void setAngle2(int angle);
    void setAngle3(int angle);
    void onTimerTimeout();
    void onTimerTimeout1();
    void onTimerTimeout2();
    void loadFile();
    void saveFile();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
    int angle1 = 30;
    int angle2 = 45;
    int angle3 = 45;
    int count =1;
    int count1 =1;
    int count2 =1;
    QTimer *timer;  // QTimer 멤버 변수
    QTimer *timer1;
    QTimer *timer2;
    int direction1 = 1;
    int direction2 = 1;
    int direction3 = 1;
};

#endif
