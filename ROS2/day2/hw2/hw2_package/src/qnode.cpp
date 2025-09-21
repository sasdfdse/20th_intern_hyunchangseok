#include "hw2_package/qnode.hpp"
#include <iostream>
#include <thread>

QNode::QNode(const std::string& name) : Node(name)
{
  TurtlePublisher = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
  client_ = this->create_client<turtlesim::srv::SetPen>("/turtle1/set_pen");
}


void QNode::set_pen(int r, int g, int b, int width)
{
    auto request = std::make_shared<turtlesim::srv::SetPen::Request>();
    request->r = r;
    request->g = g;
    request->b = b;
    request->width = width;
    request->off = 0;

    client_->async_send_request(request);
}

void QNode::drawSquare()
{
    using namespace std::chrono_literals;
    auto twist = geometry_msgs::msg::Twist();

    set_pen(255, 0, 0, 7);
    for (int i = 0; i < 4; i++)
    {
        if (i == 0)
            twist.linear.x = 2.0;
        else if (i == 1)
        {
            twist.linear.x = 0.0;
            twist.linear.y = 2.0;
        }
        else if (i == 2)
        {
            twist.linear.x = -2.0;
            twist.linear.y = 0.0;
        }
        else if (i == 3)
        {
            twist.linear.x = 0.0;
            twist.linear.y = -2.0;
        }
        TurtlePublisher->publish(twist);
        std::this_thread::sleep_for(500ms);
        QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                              .arg(twist.linear.x)
                              .arg(twist.linear.y)
                              .arg(twist.angular.z);
        emit log(log_msg);
    }
}

void QNode::drawtriangle()
{
    using namespace std::chrono_literals;
    auto twist = geometry_msgs::msg::Twist();

    set_pen(0, 255, 0, 10);
    for (int i = 0; i < 5; i++)
    {
        if (i == 0)
            twist.linear.x = 2.0;
        else if (i == 1)
        {
            twist.linear.x = 2.0;
            twist.linear.y = 2.0;
        }
        else if (i == 2)
        {
            twist.linear.x = -2.0;
            twist.linear.y = 0.0;
        }
        else if (i == 3)
            twist.linear.x = -2.0;
        else if (i == 4)
        {
            twist.linear.x = 2.0;
            twist.linear.y = -2.0;
        }
        TurtlePublisher->publish(twist);
        std::this_thread::sleep_for(500ms);
        QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                              .arg(twist.linear.x)
                              .arg(twist.linear.y)
                              .arg(twist.angular.z);
        emit log(log_msg);
    }
}

void QNode::drawcircle()
{
    using namespace std::chrono_literals;
    auto twist = geometry_msgs::msg::Twist();
     set_pen(0, 0, 255, 15);


     twist.linear.x = 2.0;
     twist.angular.z = 2.0;
     TurtlePublisher->publish(twist);
     std::this_thread::sleep_for(500ms);
     QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                           .arg(twist.linear.x)
                           .arg(twist.linear.y)
                           .arg(twist.angular.z);
     emit log(log_msg);
}

void QNode::move_forward() {

    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.angular.z = 0.0; // reset
    twist.linear.x = 2.0;
    TurtlePublisher->publish(twist);
    QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                          .arg(twist.linear.x)
                          .arg(twist.linear.y)
                          .arg(twist.angular.z);

    emit log(log_msg);
}


void QNode::move_back() {
    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.angular.z = 0.0; // reset
    twist.linear.x = -2.0;
    TurtlePublisher->publish(twist);
    QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                          .arg(twist.linear.x)
                          .arg(twist.linear.y)
                          .arg(twist.angular.z);
    emit log(log_msg);
}

void QNode::turn_left() {
    twist.linear.x = 0.0; // reset
    twist.linear.y = 0.0;
    twist.angular.z = 0.0;
     twist.angular.z = 2.0;
    TurtlePublisher->publish(twist);
    QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                          .arg(twist.linear.x)
                          .arg(twist.linear.y)
                          .arg(twist.angular.z);
    emit log(log_msg);
}

void QNode::turn_right() {
    twist.linear.x = 0.0;
    twist.linear.y = 0.0;
    twist.angular.z = 0.0; // reset
    twist.angular.z = -2.0;
    RCLCPP_INFO(this->get_logger(), "Publishing Twist: linear.x=%.2f, angular.z=%.2f", twist.linear.x, twist.angular.z);
    TurtlePublisher->publish(twist);
    QString log_msg = QString("linear.x=%1, linear.y=%2, angular.z=%3")
                          .arg(twist.linear.x)
                          .arg(twist.linear.y)
                          .arg(twist.angular.z);
    emit log(log_msg);
}

