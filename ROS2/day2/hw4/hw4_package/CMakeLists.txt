cmake_minimum_required(VERSION 3.8)
project(hw4_package)

# Set C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(Qt5 COMPONENTS Widgets Core)

# Explicitly process the .ui file to generate the header
qt5_wrap_ui(UI_HEADERS ui/mainwindow.ui)

# Set Qt for automatic MOC and RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Create the GUI executable
add_executable(${PROJECT_NAME}_node 
  src/main.cpp 
  src/main_window.cpp 
  src/qnode.cpp
  include/hw4_package/main_window.hpp
  include/hw4_package/qnode.hpp
  ${UI_HEADERS}
)

# Add include directories for the GUI target
target_include_directories(${PROJECT_NAME}_node PUBLIC
  "include"
  ${CMAKE_CURRENT_BINARY_DIR} # For the generated ui_*.h
)

# Link Qt libraries to the GUI target
target_link_libraries(${PROJECT_NAME}_node Qt5::Widgets)

# Link ROS2 libraries to the GUI target
ament_target_dependencies(${PROJECT_NAME}_node
  rclcpp
  std_msgs
  sensor_msgs
)

# Install the GUI executable
install(TARGETS ${PROJECT_NAME}_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()



ament_package()



