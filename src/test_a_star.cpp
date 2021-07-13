#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_a_star");

    ros::NodeHandle n;
    Planner::Planner pl;
    pl.plan();
    ros::spin();
    return 0;
}