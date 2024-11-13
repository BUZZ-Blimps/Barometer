#include <chrono>
#include <functional>
#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "std_msgs/msg/float64.hpp"
#include "OPI_IMU.h"
#include <wiringPi.h>
#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;
using namespace std;

OPI_IMU imu;
class baropublisher : public rclcpp::Node
{
	public:
		baropublisher()
		: Node("ground_baro_publisher")//, count_(0)
		{
			imu.OPI_IMU_Setup();

			publisher_ = this->create_publisher<std_msgs::msg::Float64>("/Barometer/reading",10);
			timer_ = this->create_wall_timer(100ms, std::bind(&baropublisher::timer_callback, this));		
		}

	private:
		void timer_callback()
		{
			imu.IMU_read();

			auto message = std_msgs::msg::Float64();
			message.data = imu.pressRaw;

			RCLCPP_INFO(this->get_logger(), "Publishing: '%f'", message.data);
			publisher_->publish(message);
		}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<std_msgs::msg::Float64>:: SharedPtr publisher_;
	size_t count_;
};

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<baropublisher>());
	rclcpp::shutdown();
	return 0;
}
