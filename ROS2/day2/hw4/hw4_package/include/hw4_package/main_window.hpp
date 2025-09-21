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
  MainWindow(QNode* qnode, QWidget* parent = nullptr);
  ~MainWindow();


public slots:
  void updateJointAngles(const std::vector<double>& positions, const std::vector<std::string>& names);
  void updateJointAngle(const QString& name, int angle);


protected:
  void paintEvent(QPaintEvent* event) override;

private:
  Ui::MainWindowDesign* ui;
  QNode* qnode_;

  int angle1 = 0;
  int angle2 = 0;
  int angle3 = 0;
};

#endif  // ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_
