#ifndef ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_
#define ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_

#include <QMainWindow>
#include "qnode.hpp"
#include "ui_mainwindow.h"


class MainWindow : public QMainWindow
{
  Q_OBJECT


public:
  MainWindow(std::shared_ptr<QNode> qnode, QWidget* parent = nullptr);
  ~MainWindow();

protected:
  void keyPressEvent(QKeyEvent* event) override;

private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void updateLog(const QString& message);

  private:
  Ui::MainWindowDesign* ui;
  std::shared_ptr<QNode> qnode_;
  QTextEdit *log_text;

};









#endif  // ROS2_CREATE_QT_PKG_MAIN_WINDOW_HPP_
