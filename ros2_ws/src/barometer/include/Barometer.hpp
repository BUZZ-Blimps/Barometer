#ifndef BAROMETER_HPP
#define BAROMETER_HPP

// #include <chrono>
// #include <functional>
// #include <memory>
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/float64.hpp>

#include <wiringPi.h>

#include "OPI_IMU.hpp"

using namespace std::chrono_literals;
using namespace std;

class Barometer : public rclcpp::Node {
public:
    Barometer();

private:
    rclcpp::TimerBase::SharedPtr baro_timer_;
    rclcpp::Publisher<std_msgs::msg::Float64>:: SharedPtr baro_publisher_, temp_publisher_;

    std_msgs::msg::Float64 baro_msg_, temp_msg_;

    OPI_IMU imu_;
    size_t count_;

    void timer_callback();
};

#endif