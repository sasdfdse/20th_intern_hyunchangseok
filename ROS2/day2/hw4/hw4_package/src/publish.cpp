#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

#include "../include/hw4_package/qnode.hpp"

QNode::QNode(const std::string& name) : Node(name)
{
    publisher_ = this->create_publisher<std_msgs::msg::String>("/joint_states", 10);
}

void QNode::publishString(const std::string &text)
{
    std::string message = std_msgs::msg::String();
    message.data = text;
    publisher_->publish(message);
}


int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
