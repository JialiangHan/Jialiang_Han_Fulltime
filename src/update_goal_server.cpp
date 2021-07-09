//this file is a server for update goal
// purpose of this server is to send goal to node planner to request a path to goal

#include <ros/ros.h>
#include <jialiang_han_fulltime/UpdateGoal.h>
#include "astar.h"

bool update_goal(jialiang_han_fulltime::UpdateGoal::Request &req, jialiang_han_fulltime::UpdateGoal::Response &res){
    //planner planner(); 
}

int main(int argc, char **argv){
    ros::init(argc,argv,"update_goal_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("update_goal",update_goal);
    ros::spin();

    return 0;
}