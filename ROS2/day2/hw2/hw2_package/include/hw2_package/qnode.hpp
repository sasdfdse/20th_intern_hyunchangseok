#ifndef HW2_QNODE_HPP_
#define HW2_QNODE_HPP_

#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/srv/set_pen.hpp"
#include <QThread>
#include <string>
#include <QObject>
#include <chrono>

class QNode : public QObject, public rclcpp::Node
{
  Q_OBJECT
public:
  explicit QNode(const std::string& name);
  void publishString(const std::string &text);
  void set_pen(int r, int g, int b, int width);
  void drawSquare();
  void drawtriangle();
  void drawcircle();
  void move_forward();
  void move_back();
  void turn_left();
  void turn_right();

private:

  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr TurtlePublisher;
  rclcpp::Client<turtlesim::srv::SetPen>::SharedPtr client_;
  geometry_msgs::msg::Twist twist;


Q_SIGNALS:
  void rosShutDown();
  void newMessageReceived(QString msg);
  void log(const QString& message);
};

#endif // HW2_QNODE_HPP_
