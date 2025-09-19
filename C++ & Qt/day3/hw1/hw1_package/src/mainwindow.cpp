#include "../include/mainwindow.h"
#include <QtGlobal>
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include "ui_mainwindow.h"
#include <QKeyEvent>


MyWidget::MyWidget(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow), count(0)
{
    ui->setupUi(this);  // 초기화

}

void MyWidget::flashBackground()
{

    originalPalette = ui->textEdit->palette();

    QPalette p = ui->textEdit->palette();
    p.setColor(QPalette::Base, QColor(Qt::yellow)); // 잠깐 노란색
    ui->textEdit->setPalette(p);


    QTimer::singleShot(200, this, [=]() {
        ui->textEdit->setPalette(originalPalette);
    });
}

void MyWidget::saveFile()
{
    QFile file("input_text.txt");

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&file);

        out << ui->textEdit->toPlainText() << "\n";

        file.close();
        std::cout << "input_text.txt 저장 완료\n";
    }
    else
    {
        std::cout << "오류 발생";
    }
}

void MyWidget::confirmPrevious()
{
    if (!tempText.isEmpty()) {
        confirmedText += tempText;
        tempText.clear();           // 임시 글자 초기화
    }

}


void MyWidget::on_pushButton_clicked()
{
    if (lastButtonClicked != 1) {confirmPrevious(); count =-1; flashBackground();}
    lastButtonClicked = 1;

    count++;
    int choice = count % 4;
    switch(choice){
    case 0: tempText = "."; break;
    case 1: tempText = ","; break;
    case 2: tempText = "?"; break;
    case 3: tempText = "!"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_2_clicked()
{
    if (lastButtonClicked != 2) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 2;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "a"; break;
    case 1: tempText = "b"; break;
    case 2: tempText = "c"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_3_clicked()
{
    if (lastButtonClicked != 3) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 3;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "d"; break;
    case 1: tempText = "e"; break;
    case 2: tempText = "f"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}

// 4번 버튼 - 지우기
void MyWidget::on_pushButton_4_clicked()
{
    if (!tempText.isEmpty()) {
        // 아직 확정되지 않은 글자가 있으면 그냥 삭제
        tempText.clear();
    } else if (!confirmedText.isEmpty()) {
        // 마지막 확정 글자 삭제
        confirmedText.chop(1);
    }


    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}



void MyWidget::on_pushButton_5_clicked()
{
    if (lastButtonClicked != 5) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 5;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "g"; break;
    case 1: tempText = "h"; break;
    case 2: tempText = "i"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_6_clicked()
{
    if (lastButtonClicked != 6) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 6;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "j"; break;
    case 1: tempText = "k"; break;
    case 2: tempText = "l"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_7_clicked()
{
    if (lastButtonClicked != 7) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 7;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "m"; break;
    case 1: tempText = "n"; break;
    case 2: tempText = "o"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}

// 8번 버튼 - 줄바꿈
void MyWidget::on_pushButton_8_clicked()
{
    confirmPrevious();


    confirmedText += "\n";
    tempText.clear();


    ui->textEdit->setPlainText(confirmedText + tempText);


    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->textEdit->setTextCursor(cursor);
    ui->textEdit->ensureCursorVisible();

    lastButtonClicked = 8;
}



void MyWidget::on_pushButton_9_clicked()
{
    if (lastButtonClicked != 9){confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 9;

    count++;
    int choice = count % 4;
    switch(choice){
    case 0: tempText = "p"; break;
    case 1: tempText = "q"; break;
    case 2: tempText = "r"; break;
    case 3: tempText = "s"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_10_clicked()
{
    if (lastButtonClicked != 10){confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 10;

    count++;
    int choice = count % 3;
    switch(choice){
    case 0: tempText = "t"; break;
    case 1: tempText = "u"; break;
    case 2: tempText = "v"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_11_clicked()
{
    if (lastButtonClicked != 11) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 11;

    count++;
    int choice = count % 4;
    switch(choice){
    case 0: tempText = "w"; break;
    case 1: tempText = "x"; break;
    case 2: tempText = "y"; break;
    case 3: tempText = "z"; break;
    }

    if (ShiftOn) tempText = tempText.toUpper();
    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);
}


void MyWidget::on_pushButton_12_clicked()
{
    ShiftOn = !ShiftOn;  // 클릭할 때마다 상태 토글
    QList<QPushButton*> buttons = {
        ui->pushButton, ui->pushButton_2, ui->pushButton_3,
        ui->pushButton_5, ui->pushButton_6, ui->pushButton_7,
        ui->pushButton_9, ui->pushButton_10, ui->pushButton_11
    };

    if(ShiftOn) {

        for(auto btn : buttons) {
            QString text = btn->text();
            btn->setText(text.toUpper());
        }
    } else {

        for(auto btn : buttons) {
            QString text = btn->text();
            btn->setText(text.toLower());
        }
    }
}
void MyWidget::on_pushButton_13_clicked()
{
   //특수문자
}

void MyWidget::on_pushButton_14_clicked()
{
   // 한/영 전환
}

void MyWidget::on_pushButton_15_clicked()
{

}

// 띄어쓰기
void MyWidget::on_pushButton_16_clicked()
{
    if (lastButtonClicked != 16) {confirmPrevious(); count =-1;flashBackground();}
    lastButtonClicked = 16;

    tempText = " ";

    ui->textEdit->setPlainText(confirmedText + tempText);
    ui->textEdit->moveCursor(QTextCursor::End);

}

void MyWidget::on_pushButton_17_clicked()
{
    //quick
}



void MyWidget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {

        saveFile();

        event->accept();
        return;
    }

    // 엔터가 아닌 키는 무시
    event->ignore();
}


