#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_get_plan");

    ros::NodeHandle nh("~");

    geometry_msgs::PoseStamped goal;
    goal.pose.position.x = 8;
    goal.pose.position.y = 8;
    goal.pose.position.z = 0;

    Planner plan("agent_1",goal);

    nav_msgs::Path nav_path;

    ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("path",1);
    nav_path = plan.call_service("agent_1",goal);
    ros::Rate loop_rate(1);

    while(ros::ok()){
        path_pub.publish(nav_path);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}