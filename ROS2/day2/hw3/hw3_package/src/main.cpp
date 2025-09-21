#include <QApplication>
#include <thread>
#include "../include/hw3_package/main_window.hpp"
#include "../include/hw3_package/qnode.hpp"

void spin_ros_node(std::shared_ptr<QNode> node)
{
  rclcpp::spin(node);
}

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto qnode = std::make_shared<QNode>("hw3_package_ui");

  QApplication a(argc, argv);
  MainWindow w(qnode);
  w.show();

  std::thread ros_thread(spin_ros_node, qnode);

  int result = a.exec();

  rclcpp::shutdown();
  if (ros_thread.joinable()) {
      ros_thread.join();
  }

  return result;
}
