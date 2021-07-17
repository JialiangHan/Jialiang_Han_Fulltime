#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_planner");

    ros::NodeHandle nh;
    
    geometry_msgs::PoseStamped goal;
    goal.pose.position.x = 8;
    goal.pose.position.y = 8;
    goal.pose.position.z = 0;
    
    Planner plan("agent_1",goal);
    // ros::spinOnce();
    
    nav_msgs::Path nav_path;
    // plan.plan();
    // nav_path = plan.get_path();
    ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("path",1);
    // ROS_INFO()
    ros::Rate loop_rate(1);

    while(ros::ok()){
        plan.plan();
        nav_path = plan.get_path();
        path_pub.publish(nav_path);
        // path_pub.publish(pl.get_path());
        ros::spinOnce();
        loop_rate.sleep();
    }
    // this function is a must or spinOnce;
    // ros::spin();
    return 0;
}