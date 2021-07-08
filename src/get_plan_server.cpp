//this file is a server for get plan
// purpose of this server is to get path from start to goal

#include <ros/ros.h>
#include "astar.h"

using namespace planner;

bool get_plan(jialiang_han_fulltime::GetPlan::Request &req, jialiang_han_fulltime::GetPlan::Response &res){
    res = Astar::planning(req.start, req.goal, req.width, req.height);
    return true;
}

int main(int argc, char **argv){
    ros::init(argc,argv,"get_plan_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("get_plan",get_plan);
    ros::spin();

    return 0;
}