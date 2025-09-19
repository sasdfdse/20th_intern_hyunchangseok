#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>

#include "ui_mainwindow.h"
#include <QGridLayout>
#include <queue>
#include <vector>
#include <cmath>

class MyWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:

public slots:


private slots:
    void on_pushButton_clicked();
    void on_spinBox_valueChanged(int arg);  // 슬롯 선언

    void Dijkstra_algorithm();
    void AStar_algorithm();
    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_2_clicked(bool checked);

    void on_spinBox_3_valueChanged(int arg1);

    void on_pushButton_3_clicked(bool checked);

private:
    Ui::MainWindow *ui;   // ui 멤버 변수
    int Col =0;
    int Row = 0;

    int obstacle_percentage=0;


    int startRow = -1;
    int startCol = -1;
    int endRow   = -1;
    int endCol   = -1;
    int startRow1 = -1;
    int startCol1 = -1;
    int endRow1   = -1;
    int endCol1   = -1;

    QGridLayout *gridLayout;
    QGridLayout *gridLayout2;

    std::vector<std::vector<bool>> obstacles;  // << 클래스 멤버


};

#endif
