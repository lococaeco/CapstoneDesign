cmake_minimum_required(VERSION 3.0.2)
project(serial_control)

find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  Total_msgs
)

catkin_package()

include_directories(
  ${catkin_INCLUDE_DIRS}
)

catkin_install_python(PROGRAMS
  src/serial_control.py
  src/serial_control_test.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
