#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_a_star");

    // ros::NodeHandle n;
    geometry_msgs::PoseStamped goal;
    goal.pose.position.x = 3;
    goal.pose.position.y=3;
    goal.pose.position.z=0;
    Planner pl("agent_1",goal);
    pl.plan();
    ros::spin();
    return 0;
}