cmake_minimum_required(VERSION 3.0.2)
project(serial_encoder)

find_package(catkin REQUIRED COMPONENTS
  rospy
  Total_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_install_python(PROGRAMS
  src/serial_encoder.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
