#include <ros/ros.h>
#include "astar.h"
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_a_star");

    ros::NodeHandle n;
   
    ros::Publisher pub = n.advertise<nav_msgs::Path>("path",1);
    geometry_msgs::PoseStamped start;
    geometry_msgs::PoseStamped goal;
    start.pose.position.x = 1;
    start.pose.position.y = 1;
    start.pose.position.z = 0;
    goal.pose.position.x = 9;
    goal.pose.position.y = 9;
    goal.pose.position.z = 0;
    nav_msgs::Path path;
    Astar a;
    path = a.planning(start,goal,10,10);
    
    ros::Rate loop_rate(1);

    while (ros::ok()){
        pub.publish(path);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}