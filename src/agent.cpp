// this file create an agent node
// publish current position on topic "agent_feedback"
// a service "update_goal" to call planner for a path

#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"
#include "geometry_msgs/PoseStamped.h"

int main(int argc,char **argv){

    ros::init(argc, argv, "agent");

    ros::NodeHandle n;

    int initial_position_x;
    int initial_position_y;
    int initial_position_theta;
    n.param<int>("x",initial_position_x, 0);
    n.param<int>("y",initial_position_y, 0);
    n.param<int>("theta",initial_position_theta, 0);
    
    ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("agent_feedback",1);
    geometry_msgs::PoseStamped current_position;

    current_position.header.frame_id = "current_position";
    current_position.header.stamp = ros::Time::now();
    current_position.pose.position.x = initial_position_x; // unit is meter
    current_position.pose.position.y = initial_position_y; //unit is meter
    current_position.pose.position.z = initial_position_theta; //unit is degree
    
    ros::Rate loop_rate(0.5);

    while (ros::ok()){
        pub.publish(current_position);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}