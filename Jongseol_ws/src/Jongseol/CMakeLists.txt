cmake_minimum_required(VERSION 3.0.2)
project(Jongseol)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  nav_msgs
  pcl_conversions
  pcl_ros
  std_msgs
  message_generation
)
find_package(yaml-cpp REQUIRED)

add_message_files(
  FILES
  init.msg
  obj.msg
  objs.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS
  roscpp 
  sensor_msgs
  std_msgs
  nav_msgs
  message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
  include
  src
)

add_executable(main
               src/main.cpp
               src/global/global.cpp
               src/parser/parser.cpp
               src/lidar/lidar.cpp
               src/imu/imu.cpp
               src/planning/planning.cpp
               src/control/control.cpp
              )

target_link_libraries(main
  ${catkin_LIBRARIES}
  -lpthread -lncurses yaml-cpp
)

add_executable(grid
               src/grid/grid.cpp
              )

target_link_libraries(grid
  ${catkin_LIBRARIES}
)

#add_dependencies(serial_data_reader ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#
#install(TARGETS serial_data_reader
#  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#)
