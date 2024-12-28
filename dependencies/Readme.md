Livox MID-360 PC IP
		IP : 192.168.1.50
		Netmask : 255.255.255.0

		Livox MID-360 IP : 192.168.1.134

Livox SDK2

		$ cd ~/Jongseol_2024/Livox-SDK2
		$ mkdir build
		$ cd build
		$ cmake .. && make -j
		$ sudo make install

Livox Driver ROS

		$ cd ~/Jongseol_2024/Livox_ws/src/livox_ros_driver2
		$ source /opt/ros/noetic/setup.bash
		$ ./build.sh ROS1

Livox Driver launch
	  	$ source ~/Jongseol_2024/Livox_ws/devel/setup.bash
		$ roslaunch livox_ros_driver2 rviz_MID360.launch
		
Convinient
		& gedit ~/.bashrc
		
source /opt/ros/noetic/setup.bash
source /home/jongseol/Jongseol_2024/Jongseol_ws/devel/setup.bash
alias ss='source ~/Jongseol_2024/Livox_ws/devel/setup.bash'

alias lidar='source ~/Jongseol_2024/Livox_ws/devel/setup.bash && roslaunch livox_ros_driver2 rviz_MID360.launch'
alias main='source ~/Jongseol_2024/Jongseol_ws/devel/setup.bash && rosrun Jongseol main'

		
		& source ~/.bashrc

open3d_slam
	Glog :
		sudo apt install libgoogle-glog-dev

	GLFW :
		sudo apt-get install libglfw3 libglfw3-dev

	ROS dependencies :
		sudo apt install ros-noetic-jsk-rviz-plugins

	LUA :
		sudo apt install liblua5.2-dev

	open3d-slam :
		sudo add-apt-repository ppa:roehling/open3d
		sudo apt update
		sudo apt install libopen3d-dev
		catkin build open3d_catkin -DCMAKE_BUILD_TYPE=Release