# people_tracker
Before running the code, make sure that the following dependencies are included  
leg_detector  
roscpp  
std_msgs  
rospy  
people_msgs 	// this is my publisher with x,y coordinates and updated person ID  
message_runtime  
visualization_msgs  
Open a terminal and following the below commands  
roscore  
Open a terminal and following the below commands  
cd ~/catkin_ws  
source ./devel/setup.bash  
Roslaunch leg_detector leg_detector  
Open a terminal and following the below commands  
Change directory to where the bag file is available  
Rosbag play -l NAME_OF_THE_BAG_FILE.bag  
Open a terminal and following the below commands  
cd ~/catkin_ws  
source ./devel/setup.bash  
catkin_make  
rosrun beginner_tutorials beginner_tutorials_node  
Open a terminal and following the below commands  
cd ~/catkin_ws  
source ./devel/setup.bash  
rosrun rviz rviz  
Set Fixed frame: base_laser_link  
Add MarkerArray  
Open a terminal and following the below commands  
cd ~/catkin_ws  
source ./devel/setup.bash  
Rostopic list // check if people_msgs/PositionMeasurementArray is available  
Rosmsg show people_msgs/positionMeasurementArray  

