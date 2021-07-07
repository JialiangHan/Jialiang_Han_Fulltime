//this file is a server for update goal
// purpose of this server is to send goal to node planner to request a path to goal

#include <ros/ros.h>
#include "astar.h"

bool update(&req,&res){
    planner planner(); 
}

int main(int argc, char **argv){
    ros::init(argc,argv,"update_goal_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("update_goal",update);
    ros::spin();

    return 0;
}