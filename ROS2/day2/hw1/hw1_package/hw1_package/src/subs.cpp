#include "rclcpp/rclcpp.hpp"

#include <chrono>
#include <memory>
#include <functional>
#include "../include/hw1_package/qnode.hpp"
#include "../include/hw1_package/main_window.hpp"




MyNode::MyNode() : Node("mynode")
{

    subscriber = this->create_subscription<std_msgs::msg::String>("topicname", 10, std::bind(&MyNode::topic_callback, this, std::placeholders::_1));


}
void MyNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {

    RCLCPP_INFO(this->get_logger(), "Subscribed to '%s'", msg ->data.c_str());

}




int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
