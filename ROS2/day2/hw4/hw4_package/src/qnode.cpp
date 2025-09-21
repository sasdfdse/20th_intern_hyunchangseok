#include "../include/hw4_package/qnode.hpp"
#include <QDebug>
#include <QStringList>

QNode::QNode(int argc, char** argv) :
  init_argc(argc),
  init_argv(argv)
{}

QNode::~QNode() {
    if(rclcpp::ok()) {
        rclcpp::shutdown();
    }
    wait();
}

bool QNode::init() {
    rclcpp::init(init_argc, init_argv);
    node_ = std::make_shared<rclcpp::Node>("hw4_package_node");

    auto command_callback =
      [this](const std_msgs::msg::String::SharedPtr msg) -> void
      {
        QString q_msg = QString::fromStdString(msg->data);
        QStringList parts = q_msg.split(" ");
        if (parts.length() == 2) {
            QString name = parts[0];
            bool ok;
            int angle = parts[1].toInt(&ok);
            if (ok) {
                Q_EMIT commandReceived(name, angle);
            }
        }
      };

    command_subscriber_ = node_->create_subscription<std_msgs::msg::String>(
      "/gui_command", qos, command_callback, subscription_options);

    this->start();
    return true;
}

void QNode::run() {
    rclcpp::spin(node_);
    Q_EMIT rosShutDown(); 
}
