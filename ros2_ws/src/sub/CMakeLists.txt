cmake_minimum_required(VERSION 3.8)
project(sub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()


find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)


  find_package(ament_lint_auto REQUIRED)
  add_executable(listener src/barosubscriber.cpp)
  ament_target_dependencies(listener rclcpp std_msgs)
  
  install(TARGETS
  	
  	listener
  	DESTINATION lib/${PROJECT_NAME})
  ament_lint_auto_find_test_dependencies()


ament_package()
