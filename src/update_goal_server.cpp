//this file is a server for update goal
// purpose of this server is to send goal to node planner to request a path to goal

#include <ros/ros.h>
#include <jialiang_han_fulltime/UpdateGoal.h>
#include "astar.h"
#include "planner.h"

using namespace planner;

bool update_goal(jialiang_han_fulltime::UpdateGoal::Request &req, jialiang_han_fulltime::UpdateGoal::Response &res){
    Planner astar(req.agent_name, req.goal);
    astar.set_get_plan_server();
    res.path = astar.call_service(req.agent_name,req.goal);
    return true;
}

int main(int argc, char **argv){
    ros::init(argc,argv,"update_goal_server");
    ros::NodeHandle n;

    ros::ServiceServer service = n.advertiseService("update_goal",update_goal);
    ros::spin();

    return 0;
}