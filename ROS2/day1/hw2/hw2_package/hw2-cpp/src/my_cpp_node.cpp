#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>
#include <functional>
#include "std_msgs/msg/float32.hpp"
class MyNode : public rclcpp::Node
{
    public:
    MyNode();
    

    private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscriber_float;
    
  
    void topic_callback(const std_msgs::msg::String::SharedPtr msg);
    void topic_double(const std_msgs::msg::Float32::SharedPtr msg1);

};
MyNode::MyNode() : Node("mynode")
{
    
  subscriber = this->create_subscription<std_msgs::msg::String>("topicname", 10, std::bind(&MyNode::topic_callback, this, std::placeholders::_1));
     
  subscriber_float = this->create_subscription<std_msgs::msg::Float32>("topicdouble", 10, std::bind(&MyNode::topic_double, this, std::placeholders::_1));



}
void MyNode::topic_callback(const std_msgs::msg::String::SharedPtr msg) {

    RCLCPP_INFO(this->get_logger(), "Subscribed to '%s'", msg ->data.c_str());
    
}
 void MyNode::topic_double(const std_msgs::msg::Float32::SharedPtr msg1){
RCLCPP_INFO(this->get_logger(), "Subscribed Double to  '%.2f'", msg1->data);
 }

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}









