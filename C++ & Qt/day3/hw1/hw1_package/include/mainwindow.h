#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"

class MyWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = nullptr);

protected:

    void keyPressEvent(QKeyEvent *event) override;

public slots:
    void saveFile();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_15_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_17_clicked();
    void confirmPrevious();
    void flashBackground();


private:
    Ui::MainWindow *ui;   // ui 멤버 변수
    bool ShiftOn = false;
    int count = -1;
    int count1 = 1;

    QTimer *timer;  // QTimer 멤버 변수 추가

    QString confirmedText;   // 이미 확정된 글자
    QString tempText;        // 현재 버튼에서 선택 중인 임시 글자
    int lastButtonClicked = -1; // 멤버 변수로 추가
    QPalette originalPalette;



};

#endif
