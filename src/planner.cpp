// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// service client: get_plan

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>


int main(int argc,char **argv){

    ros::init(argc, argv, "planner");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("agent_feedback",1);
    geometry_msgs::PoseStamped current_position;

    current_position.header.frame_id = "current_position";
    current_position.header.stamp = ros::Time::now();
    current_position.info.resolution = 1; // unit is meter
    current_position.info.width = 10; //unit is meter
    current_position.info.height = 10; //unit is meter



    while (ros::ok()){
        pub.publish(current_position);
    }

    ros::shutdown();
    return 0;
}