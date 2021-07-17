# Jialiang_Han_Fulltime

this repo is for mulit(two) agent path planning in a 10*10 grid map.

Setup

Run the following command to clone, build, and launch the package (requires a sources ROS environment):

mkdir -p ~/catkin_ws/src \
&& cd ~/catkin_ws/src \
&& git clone https://github.com/JialiangHan/jialiang_han_fulltime.git \
&& cd .. \
&& catkin_make \
&& source devel/setup.bash \
&& roslaunch jialiang_han_fulltime launch.launch

issue remaining:
1. if my understanding is correct, update goal server should be set in agent node. but this will cause issue if we start two agent node. so server should be set seperately.
2. get plan server should be set in planner node. but issue comes up, if i add server in planner, i also should add ros::spin in that. if so, i can never get out of spin.