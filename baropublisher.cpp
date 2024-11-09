#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "OPI_IMU.h"
#include <wiringPi.h>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;
using namespace std;



OPI_IMU imu;
class baropublisher : public rclcpp::Node
{
	public:
		
		baropublisher()
		: Node("baro_publisher")//, count_(0)
		{

			imu.OPI_IMU_Setup();

			publisher_ = this->create_publisher<std_msgs::msg::String>("topic",10);
			timer_ = this->create_wall_timer(100ms, std::bind(&baropublisher::timer_callback, this));		
		}
	private:
		
		
		void timer_callback()
		{
			
			imu.IMU_read();

			/*printf("ROTATION 0 DEGREES\n");
			printf("========================\n");
			printf("AccYraw: %f\n", imu.AccYraw);
			printf("AccXraw: %f\n", imu.AccXraw);
			printf("AccZraw: %f\n\n", imu.AccZraw);

			printf("MagYraw: %f\n", imu.MagYraw);
			printf("MagXraw: %f\n", imu.MagXraw);
			printf("MagZraw: %f\n\n", imu.MagZraw);

			printf("gyr_rateYraw: %f\n", imu.gyr_rateYraw);
			printf("gyr_rateXraw: %f\n", imu.gyr_rateXraw);
			printf("gyr_rateZraw: %f\n\n", imu.gyr_rateZraw);

			printf("tempRaw: %f\n", imu.tempRaw);*/
			
			printf("pressRaw: %f\n\n\n\n", imu.pressRaw);
			
			auto message = std_msgs::msg::String();
			message.data = "Pressure is " + std::to_string(imu.pressRaw);

			
			RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
			publisher_->publish(message);

		}

	rclcpp::TimerBase::SharedPtr timer_;
	rclcpp::Publisher<std_msgs::msg::String>:: SharedPtr publisher_;
	size_t count_;
};

int main(int argc, char * argv[])
{
	
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<baropublisher>());
	rclcpp::shutdown();
	return 0;

}
