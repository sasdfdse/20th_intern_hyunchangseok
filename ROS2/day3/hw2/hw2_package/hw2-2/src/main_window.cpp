#include "../include/hw2-2/main_window.hpp"
#include <QPainter>
#include <cmath>
#include <QMetaObject>
#include <yaml-cpp/yaml.h>

MainWindow::MainWindow(QWidget* parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindowDesign)
{
   ui->setupUi(this);

   // /home/bws/ros2_create_qt_pkg/hw4/config/ 경로에 있는 YAML파일을 열어 config 변수에 저장
   YAML::Node config = YAML::LoadFile("/home/bws/ros2_create_qt_pkg/hw2-2/config/params.yaml");

   angle1 = config["hw2-2_node"]["ros__parameters"]["first_angle"][0].as<int>();   // 객체가 생성될 때 hw4_node에서 ros__parameters라는 네임 스페이스 안에 first_angle 데이터 배열의 첫 번째 원소를 정수형으로 저장한다.
   angle2 = config["hw2-2_node"]["ros__parameters"]["first_angle"][1].as<int>();  // .. 2번 째 요소를 저장
   angle3 = config["hw2-2_node"]["ros__parameters"]["first_angle"][2].as<int>();  // .. 3번 째 요소를 저장

   link_lengths_[0] =  config["hw2-2_node"]["ros__parameters"]["link_length"][0].as<double>(); // .. link_length 데이터 배열의 첫 번째 요소를 실수형으로 저장
   link_lengths_[1] =  config["hw2-2_node"]["ros__parameters"]["link_length"][1].as<double>(); // .. link_length 데이터 배열의 두 번째 요소를 실수형으로 저장
   link_lengths_[2] =  config["hw2-2_node"]["ros__parameters"]["link_length"][2].as<double>(); // .. link_length 데이터 배열의 세 번째 요소를 실수형으로 저장
}

MainWindow::~MainWindow()
{
  delete ui;
}



void MainWindow::updateJointAngles(const std::vector<double>& positions, const std::vector<std::string>& names)
{

    for (size_t i = 0; i < names.size(); ++i)
    {

        int degree = static_cast<int>(positions[i] * 180.0 / M_PI);

        if (names[i] == "joint1")
        {
            angle1 = qBound(0, degree, 360);
        }
        else if (names[i] == "joint2")
        {
            angle2 = qBound(0, degree, 360);
        }
        else if (names[i] == "joint3")
        {
            angle3 = qBound(0, degree, 360);
        }
    }
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.save();
    painter.translate(300, 300);  //팔1 시작점  // 초기화
    painter.rotate(angle1);
    painter.drawLine(0, 0, link_lengths_[0], 0);  // 팔 1

    painter.translate(link_lengths_[0], 0);  // 팔 1끝으로 이동
    painter.rotate(angle2);
    painter.drawLine(0, 0, link_lengths_[1], 0);   // 팔 2

    painter.translate(link_lengths_[1], 0);  // 팔 2끝으로 이동
    painter.rotate(angle3);
    painter.drawLine(0, 0, link_lengths_[2], 0);   // 팔 3

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
