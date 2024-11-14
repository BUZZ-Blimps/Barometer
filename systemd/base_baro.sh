#!/bin/bash
export ROS_DOMAIN_ID=1
source /opt/ros/humble/setup.bash
source /home/opi/ros2_ws/install/setup.bash
ros2 run barometer barometer_node