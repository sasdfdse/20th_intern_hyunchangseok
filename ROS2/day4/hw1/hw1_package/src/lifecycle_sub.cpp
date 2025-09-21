#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
using std::placeholders::_1; // 바인드 함수 사용시 첫 번째 인자를 항상 사용하겠다는 뜻 

#include "hw1_package/lifecycle.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"

MinimalSubscriber::MinimalSubscriber() : rclcpp_lifecycle::LifecycleNode("minimal_subscriber") {
}

MinimalSubscriber::~MinimalSubscriber() {
    
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MinimalSubscriber::on_configure(const rclcpp_lifecycle::State &state)
{    
    subscription_ = this->create_subscription<std_msgs::msg::String>(  // lifecycle 정의상 subscription이 생성되는 것은 on_configure가 호출될 때 행해지는 것이 적절하기 때문이다
        "topic", rclcpp::SensorDataQoS(), std::bind(&MinimalSubscriber::topic_callback, this, _1));  // SensorDataQoS 빠른 통신 우선
    m_isActivated = false; // 이는 lifecycle node가 active한 상태는 아니라는 것을 의미한다. 
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_configure() is called from state %s.", state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MinimalSubscriber::on_activate(const rclcpp_lifecycle::State &state)
{
    m_isActivated = true;
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_activate() is called from state %s.", state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MinimalSubscriber::on_deactivate(const rclcpp_lifecycle::State &state)
{
    m_isActivated = false;
    RCUTILS_LOG_INFO_NAMED(get_name(), "on_deactivate() is called from state %s.", state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MinimalSubscriber::on_cleanup(const rclcpp_lifecycle::State &state)
{
    subscription_.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on cleanup is called from state %s.", state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn
MinimalSubscriber::on_shutdown(const rclcpp_lifecycle::State &state)
{
    subscription_.reset();
    RCUTILS_LOG_INFO_NAMED(get_name(), "on shutdown is called from state %s.", state.label().c_str());

    return rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn::SUCCESS;
}

void MinimalSubscriber::topic_callback(const std_msgs::msg::String &msg) const
{
    if (m_isActivated)
    {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg.data.c_str());
    }
    else
    {
        RCLCPP_INFO(
            this->get_logger(), "Subscriber is currently inactive. Callback function is not working .");
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    std::shared_ptr<MinimalSubscriber> minimal_subscriber = std::make_shared<MinimalSubscriber>(); //  앞서 구현했던 lifecycle node 
    rclcpp::spin(minimal_subscriber->get_node_base_interface());
    rclcpp::shutdown();
    return 0;
}
