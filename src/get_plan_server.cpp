//this file is a server for get plan
// purpose of this server is to get path from start to goal

#include <ros/ros.h>
#include <jialiang_han_fulltime/GetPlan.h>
#include "planner.h"

using namespace planner;

bool get_plan(jialiang_han_fulltime::GetPlan::Request &req, jialiang_han_fulltime::GetPlan::Response &res){
    Planner astar(req.agent_name, req.goal);
    ros::Rate loop_rate(1);
    int i =0;
    while(ros::ok()&& i<=2){
        astar.plan();
        ros::spinOnce();
        loop_rate.sleep();
        i++;
    }
    res.path = astar.get_path();
    return true;
}

int main(int argc, char **argv){
    ros::init(argc,argv,"get_plan_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("get_plan",get_plan);
    ros::spin();

    return 0;
}