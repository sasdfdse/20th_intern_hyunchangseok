#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>
#include <functional>
#include "std_msgs/msg/float32.hpp"


// class MyCppNode : public rclcpp::Node
// {   
//     public:
//     MyCppNode() : Node("my_cpp_node")
//     {
//         RCLCPP_INFO(this->get_logger(), "Hello, ROS 2 C++ Node!");
//     }
// };

class MyNode : public rclcpp::Node
{
    public:
    MyNode();
 

    private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_float;
    rclcpp::TimerBase::SharedPtr timer_;

    
    int count_=0;
    float count__ = 0; //이렇게 안하면 아뇜

    void timer_callback();
    

};

MyNode::MyNode() : Node("mynode1")
{
   publisher_ = this->create_publisher<std_msgs::msg::String>("topicname", 10);
   publisher_float = this->create_publisher<std_msgs::msg::Float32>("topicdouble", 10);
   timer_ = this->create_wall_timer(std::chrono::duration<double>(1.0), std::bind(&MyNode::timer_callback, this));




}





void MyNode::timer_callback() {

auto msg =  std_msgs::msg::String();
msg.data = "i'm C++" + std::to_string(count_++);
RCLCPP_INFO(this->get_logger(), "Published message : '%s'",msg.data.c_str());
publisher_->publish(msg);


auto msg1 =  std_msgs::msg::Float32();
count__ +=0.5; 
msg1.data += count__;
RCLCPP_INFO(this->get_logger(), "Published Double : '%.2f'",msg1.data);
publisher_float->publish(msg1);


}



int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}









