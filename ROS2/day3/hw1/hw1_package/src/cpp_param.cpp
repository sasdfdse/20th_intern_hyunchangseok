#include "my_node.hpp"
#include <chrono>
#include <functional>
#include <string>
#include <rclcpp/rclcpp.hpp>

MinimalParam::MinimalParam() : Node("minimal_param_node") { // MiniMalParam 매개변수의 생성자 호출 , 이름을 minimal_param_node 로 정의 

    this -> declare_parameter("my_parameter","world") ; // my_parameter 기본값 world

    timer_ = this -> create_wall_timer ( 1000ms, std:: bind(&MinimalParam::timer_callback,this)); // 1000ms의 시간마다 timer_callback함수를 실행하는 타이머를 생성

}

MinimalParam::~MinimalParam() {  
    
}


void  MinimalParam::timer_callback () {

std :: string my_param = this -> get_parameter("my_parameter").as_string(); // my_parameter노드에서 파라미터 저장

RCLCPP_INFO (this -> get_logger(), "Hello %s!", my_param.c_str()); // my_param에 저장된 문자열 로그로 출력 

std::vector<rclcpp::Parameter> all_new_parameters{rclcpp::Parameter("my_parameter","world")}; // "my_parameter"라는 이름을 가진 파라미터를 생성 후 "world"라는 string으로 기본값 설정
this->set_parameters(all_new_parameters); // 여러 개를 한 번에 세팅할 수 있도록 std::vector 형태로 파라미터를 모음 //all_new_parameters 벡터 안에 들어있는 파라미터들을 노드에 한꺼번에 반영


}

int main (int argc, char **argv) {

rclcpp::init(argc,argv); //ROS 2 초기화
rclcpp::spin(std::make_shared<MinimalParam>());  // MinimalParam클래스 구성. rclcpp::spin노드에서 데이터를 처리하기 시작
rclcpp::shutdown();
return 0;

}