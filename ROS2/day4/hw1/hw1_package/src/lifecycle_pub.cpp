#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "hw1_package/lifecycle.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"   // 일반 노드를 생성할 때 주로 사용했던 헤더 파일들 

#include "rclcpp_lifecycle/lifecycle_node.hpp" // lifecycle 노드를 만들기 위해 필요한 데이터 

using namespace  std :: chrono_literals;

    MinimalPublisher::MinimalPublisher() : rclcpp_lifecycle::LifecycleNode("minimal_publisher"), count_(0) {
        // publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        // timer_ = this->create_wall_timer(
    //     500ms, std::bind(&MinimalPublisher::timer_callback, this));  

    // 본래 노드를 생성할 때 선언하던 부분을 사용하지 않는다 
   
}

MinimalPublisher::~MinimalPublisher() {}

// 이곳에서 publisher/subscriber, timer, service 등을 생성
rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn MinimalPublisher::on_configure(const rclcpp_lifecycle::State &state) //unconfigure 상태에서 inactive 상태로 변환 
{
    //  QoS(베스트 에포트) // SensorDataQoS 빠른 통신 우선 
    publisher_ = this -> create_publisher <std_msgs::msg::String>("topic", rclcpp::SensorDataQoS()); //topic 이라는 이름의 토픽에 퍼블리시하는 퍼블리셔 생성 
    timer_  = this -> create_wall_timer(1s,std::bind(&MinimalPublisher::timer_callback,this));  // 일정 시간마다 퍼블리시를 하기 위해 1초마다 타이머가 작동해 콜백함수를 호출함

    RCUTILS_LOG_INFO_NAMED(this->get_name(), "on_configured () is called from state %s",state.label().c_str());  // 상태 로그 출력

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS; // 성공적으로 동작했으면 성공했다는 것을 반환함
}


rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn MinimalPublisher::on_activate(const rclcpp_lifecycle::State &state) //inactive에서 active로. 실제로 publisher/subscriber 등이 데이터를 생성 및 처리
 {
    publisher_ -> on_activate(); //inactive -> active로 lifecycle node의 상태 변환

    RCUTILS_LOG_INFO_NAMED(this->get_name(),"on_activate() is called from state %s.", state.label().c_str()); // // 상태 로그 출력

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS; //// 성공적으로 동작했으면 성공했다는 것을 반환함
 }


rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn MinimalPublisher::on_deactivate(const rclcpp_lifecycle::State &state) //active 상태에서 inactive 상태로 변환 
{
    publisher_ -> on_deactivate();  // active에서 inactive로 node의 상태를 변환// timer callback에서 publisher_를 통해 퍼블리시 해도 기능을 하지 못함
    RCUTILS_LOG_INFO_NAMED(this->get_name(), "on_deactivate() is called from state %s", state.label().c_str()); 

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;   // 성공적으로 동작했으면 성공했다는 것을 반환함
}


 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn MinimalPublisher::on_cleanup(const rclcpp_lifecycle::State &state) //configure를 하기 전에 생성되었던 publisher/subscriber, service, 필요없는 변수들을 청소
{   //inactive에서 unconfigured로 변경
    timer_.reset();  // 이전에 생성했던 timer 
    publisher_.reset(); // publisher의 메모리를 해제.

    RCUTILS_LOG_INFO_NAMED(this->get_name(),"on cleanup is called from state %s.",state.label().c_str()); // 상태 로그 출력

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS; // 성공적으로 동작했으면 성공했다는 것을 반환함
}

// node가 기능을 잃기전 안전하게 필요없는 메모리를 해제하는 역할
rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn MinimalPublisher::on_shutdown(const rclcpp_lifecycle::State &state)  
{
    timer_.reset();  // 이전에 생성했던 timer 
    publisher_.reset(); // publisher의 메모리를 해제.

    RCUTILS_LOG_INFO_NAMED(this->get_name(),"on shutdowm is called from state %s.",state.label().c_str()); // 상태 로그 출력

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS; // 성공적으로 동작했으면 성공했다는 것을 반환함
}


void MinimalPublisher::timer_callback () {
    auto message = std_msgs::msg::String();
    message.data = std::string("message_tranported") + std::to_string(count_++);
 
    // publisher_가 active상태인지 확인하고 상태에 따라 log를 출력한다. 
    if(!publisher_-> is_activated())
    {
        RCLCPP_INFO(this->get_logger(), "Lifecycle publisher is currently inactive. Messages are not published");
    }
    else 
    {
        RCLCPP_INFO(this->get_logger(), "Lifecycle publisher is active. Publishing [%s]",message.data.c_str());
        publisher_->publish(message);
    }
}


int main(int argc, char *argv[])
{
    rclcpp::init(argc,argv);
    std::shared_ptr<MinimalPublisher> minimal_publisher = std::make_shared<MinimalPublisher>();
    rclcpp::spin(minimal_publisher->get_node_base_interface()); // spin 사용시 기존 노드를 사용할 때 class 자체를 넣는 것이 아닌 
    //node의 base interface를 넣는다.
    rclcpp::shutdown();

    return 0;
}
