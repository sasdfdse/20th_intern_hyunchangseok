
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef ROS2_CREATE_QT_PKG_QNODE_HPP_
#define ROS2_CREATE_QT_PKG_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/
#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"
#include <QThread>
#include <string>
#endif // Q_MOC_RUN

class MyNode : public rclcpp::Node
{
public:
    MyNode();


private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber;


    void topic_callback(const std_msgs::msg::String::SharedPtr msg);


};



class QNode : public rclcpp::Node
{
public:
  explicit QNode(const std::string& name);
  void publishString(const std::string &text);
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
protected:
  void run();

private:


  std::shared_ptr<rclcpp::Node> node;



  void topic_callback(const std_msgs::msg::String::SharedPtr msg);


Q_SIGNALS:
  void rosShutDown();
  void newMessageReceived(QString msg);
};


#endif 
