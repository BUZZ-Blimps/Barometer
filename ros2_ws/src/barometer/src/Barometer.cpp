#include "Barometer.hpp"

Barometer::Barometer() : Node("ground_baro_publisher") {
    imu_.OPI_IMU_Setup();

    baro_publisher_ = this->create_publisher<std_msgs::msg::Float64>("/Barometer/reading", 10);
    temp_publisher_ = this->create_publisher<std_msgs::msg::Float64>("/Barometer/temperature", 10);
    baro_timer_ = this->create_wall_timer(40ms, std::bind(&Barometer::timer_callback, this));
}

void Barometer::timer_callback() {
    imu_.baro_read();
    baro_msg_.data = imu_.comp_press;
    temp_msg_.data = imu_.comp_temp;

    baro_publisher_->publish(baro_msg_);
    temp_publisher_->publish(temp_msg_);

    // RCLCPP_INFO(this->get_logger(), "Raw: %.2f, Comp: %.2f, Temp: %.2f", imu_.pressRaw, imu_.comp_press, imu_.comp_temp);
}
