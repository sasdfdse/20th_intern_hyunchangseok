#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

#include "../include/hw2-2/qnode.hpp"



MinimalParam::MinimalParam() : Node("minimal_param_node") { // MiniMalParam 매개변수의 생성자 호출 , 이름을 minimal_param_node 로 정의

    this->declare_parameter<std::vector<double>>("link_length", std::vector<double>()); //
    this->declare_parameter<std::vector<double>>("first_angle", std::vector<double>());


}

MinimalParam::~MinimalParam() {

}


void  MinimalParam::timer_callback () {

    std::vector<double> link_lengths = this->get_parameter("link_length").as_double_array();
    std::vector<double> initial_angles = this->get_parameter("first_angle").as_double_array();


    }


