#pragma once

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <string>
#include <vector>
#include <thread>
#include <chrono>


using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node 
{
    public: 
      MinimalParam();
      ~MinimalParam();

      void timer_callback();

    private :
     rclcpp::TimerBase::SharedPtr timer_;

};



class MyNode : public rclcpp::Node
{
public:
    MyNode();

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;
    void topic_callback(const std_msgs::msg::String::SharedPtr msg);
};

class MyNode1 : public rclcpp::Node
{
public:
    MyNode1();
    ~MyNode1();

private:
    void input_thread_func();
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::thread input_thread_;
    std::string sendstring;
    std::vector<std::string> queue_v;
};


