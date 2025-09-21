#include <QApplication>
#include "../include/hw2-2/main_window.hpp"
#include "../include/hw2-2/qnode.hpp"
#include <thread>

int main(int argc, char* argv[])
{
  rclcpp::init(argc, argv);
  auto minimal_param_node = std::make_shared<MinimalParam>();
  
  std::thread ros_thread([&]() {
    rclcpp::spin(minimal_param_node);
  });

  QApplication a(argc, argv);

  MainWindow w(nullptr);
  w.show();

  int result = a.exec();

  rclcpp::shutdown();
  ros_thread.join();

  return result;
}
