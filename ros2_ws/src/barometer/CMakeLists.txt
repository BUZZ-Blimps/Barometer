cmake_minimum_required(VERSION 3.8)
project(barometer)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)  
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(
    ${PROJECT_NAME}_node
    src/Barometer.cpp
    src/OPI_IMU.cpp
    src/barometer_node.cpp
)

ament_target_dependencies(
    ${PROJECT_NAME}_node 
    rclcpp 
    std_msgs
)

target_include_directories(
    ${PROJECT_NAME}_node PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(${PROJECT_NAME}_node wiringPi)

install(
    TARGETS ${PROJECT_NAME}_node
    DESTINATION lib/${PROJECT_NAME}
)

ament_package()
