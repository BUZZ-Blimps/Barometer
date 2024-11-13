#include "Barometer.hpp"

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<Barometer>());
    rclcpp::shutdown();
    return 0;
}
