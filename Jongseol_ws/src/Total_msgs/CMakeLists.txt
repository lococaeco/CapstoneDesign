cmake_minimum_required(VERSION 3.0.2)
project(Total_msgs)

find_package(catkin REQUIRED COMPONENTS
  message_generation
)

add_message_files(
  FILES
  Control.msg
  Encoder.msg
)

generate_messages(
  DEPENDENCIES
)

catkin_package(
  CATKIN_DEPENDS message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
