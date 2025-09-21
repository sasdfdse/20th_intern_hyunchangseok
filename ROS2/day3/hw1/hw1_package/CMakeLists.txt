cmake_minimum_required(VERSION 3.14)
project(hw1_package)

set(hw1_package_MAJOR_VERSION 0)
set(hw1_package_MINOR_VERSION 0)
set(hw1_package_PATCH_VERSION 0)
set(hw1_package_VERSION
  ${hw1_package_MAJOR_VERSION}.${hw1_package_MINOR_VERSION}.${hw1_package_PATCH_VERSION})

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


# find dependencies
find_package(rclpy REQUIRED)
find_package(std_msgs REQUIRED)
