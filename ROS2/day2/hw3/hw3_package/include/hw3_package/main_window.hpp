#ifndef ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_
#define ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_

#include <QMainWindow>
#include "qnode.hpp"
#include "ui_mainwindow.h"
#include <vector>
#include <string>


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(std::shared_ptr<QNode> qnode, QWidget* parent = nullptr);
  ~MainWindow();


private slots:
  void on_pushButton_clicked();

private:
  Ui::MainWindowDesign* ui;
  std::shared_ptr<QNode> qnode_;
    QTextEdit *log;
  QVector< QString > queue_v;
};



















#endif  
