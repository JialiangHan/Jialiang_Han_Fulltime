// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// subscrible grid map to get map info
// service client: get_plan

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "astar.h"
#include "node_3d.h"

using namespace planner;

int width;
int height;
geometry_msgs::PoseStamped current_position;

void map_callback(nav_msgs::OccupancyGrid msg){
    width = msg.info.width;
    height = msg.info.height;
}

void agent_feedback_callback(geometry_msgs::PoseStamped msg){
    current_position = msg
}

int main(int argc,char **argv){

    ros::init(argc, argv, "planner");

    ros::NodeHandle n;
    // subscribe map info
    ros::Subscriber map_sub = n.subscribe("grid_map", 1, map_callback);
    // subscribe agent current postion
    string agent_name;
    agent_name = atoll(argv[1]);
    string topic_name;
    topic_name = agent_name +“/agent_feedback";
    ros::Subscriber agent_feedback_sub = n.subscribe("agent_feedback", 1, agent_feedback_callback);
    //call get plan service
    ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
    jialiang_han_fulltime::GetPlan srv;
    srv.request.start = current_position;
    srv.request.goal = atoll(argv[2]);
    srv.request.width = width;
    srv.request.height = height;


    ros::shutdown();
    return 0;
}