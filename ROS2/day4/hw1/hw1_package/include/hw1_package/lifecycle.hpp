#include <chrono>
#include <functional>
#include <memory>
#include <string>


#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"   // 일반 노드를 생성할 때 주로 사용했던 헤더 파일들 

#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include "rclcpp_lifecycle/lifecycle_publisher.hpp"

class MinimalPublisher : public rclcpp_lifecycle::LifecycleNode // 라이프사이클 노드를 상속하는 클래스 선언
{
public :
 MinimalPublisher();   // 셍성자 
 ~MinimalPublisher();   // 소멸자 

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_configure(const rclcpp_lifecycle::State &state); //unconfigure 상태에서 inactive 상태로 변환 
 //(publisher/subscriber, timer, service 등 생성)

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_activate(const rclcpp_lifecycle::State &state); //inactive -> active로 lifecycle node의 상태 변환

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &state); //active에서 inactive로 node의 상태를 변환

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State &state); //inactive에서 unconfigured로 변경

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State &state); 

 private :
 void timer_callback(); 

 rclcpp::TimerBase::SharedPtr timer_; // 메세지를 퍼블리시하는데 필요한 timer 
 std::shared_ptr<rclcpp_lifecycle::LifecyclePublisher<std_msgs::msg::String>> publisher_; // 메세지를 퍼블리시하는 퍼블리셔,  활성화/비활성화 할 수 있는 publisher : LifecyclePublisher 타입
 size_t count_;  // 메세지 퍼블리시 카운트 



}; 

class MinimalSubscriber : public rclcpp_lifecycle::LifecycleNode // 라이프사이클 노드를 상속하는 클래스 선언
{
public :
 MinimalSubscriber();   // 셍성자 
 ~MinimalSubscriber();   // 소멸자 

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_configure(const rclcpp_lifecycle::State &state); //unconfigure 상태에서 inactive 상태로 변환 
 //(publisher/subscriber, timer, service 등 생성)

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_activate(const rclcpp_lifecycle::State &state); //inactive -> active로 lifecycle node의 상태 변환


 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_deactivate(const rclcpp_lifecycle::State &state); //active에서 inactive로 node의 상태를 변환

 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_cleanup(const rclcpp_lifecycle::State &state); //inactive에서 unconfigured로 변경

    
 rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn on_shutdown(const rclcpp_lifecycle::State &state); 

 private :
 void topic_callback(const std_msgs::msg::String & msg) const; 
 
 rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
 
 bool m_isActivated = false;  // active 인지 inactive 인지 정의하는 bool
}; 
