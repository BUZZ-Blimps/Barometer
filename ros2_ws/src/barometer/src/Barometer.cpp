#include "Barometer.hpp"

Barometer::Barometer() : Node("ground_baro_publisher") {
    imu_.OPI_IMU_Setup();

    publisher_ = this->create_publisher<std_msgs::msg::Float64>("/Barometer/reading",10);
    timer_ = this->create_wall_timer(100ms, std::bind(&Barometer::timer_callback, this));       
}

void Barometer::timer_callback() {
    imu_.baro_read();

    auto message = std_msgs::msg::Float64();
    message.data = imu_.pressRaw;

    RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
    publisher_->publish(message);
}
