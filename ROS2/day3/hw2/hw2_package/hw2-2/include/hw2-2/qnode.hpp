
#ifndef ROS2_CREATE_QT_PKG_QNODE_HPP_
#define ROS2_CREATE_QT_PKG_QNODE_HPP_



#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include <QThread>
#include <QString>
#include <string>
#include <vector>
#include <functional> // For std::function
#endif // Q_MOC_RUN

class QNode : public QThread
{
  Q_OBJECT
public:
  QNode(int argc, char** argv);
  virtual ~QNode();
  bool init();
  void run();

private:
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_subscriber;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr command_subscriber_;

  int init_argc;
  char** init_argv;
  std::shared_ptr<rclcpp::Node> node_;

signals:
  void rosShutDown();
  void jointStateReceived(const std::vector<double>&, const std::vector<std::string>&);
  void commandReceived(const QString&, int);
};

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
    using SetInitialStateCallback = std::function<void(const std::vector<double>&, const std::vector<double>&)>;
    MinimalParam();
    ~MinimalParam();

    void timer_callback();

private :
    rclcpp::TimerBase::SharedPtr timer_;
    SetInitialStateCallback set_initial_state_callback_;

};



#endif // ROS2_CREATE_QT_PKG_QNODE_HPP_

