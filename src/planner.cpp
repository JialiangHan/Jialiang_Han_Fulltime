// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// subscrible grid map to get map info
// service client: get_plan

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <map>
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
    // get topic name of specific agent
    topic_name = agent_name + "/agent_feedback";
    ros::Subscriber agent_feedback_sub = n.subscribe(topic_name, 1, agent_feedback_callback);
    //call get plan service
    ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
    jialiang_han_fulltime::GetPlan srv;
    srv.request.start = current_position;
    srv.request.goal = atoll(argv[2]);
    srv.request.width = width;
    srv.request.height = height;
    // publish path to rviz
    ros::Publisher path_pub = n.advertise<visualization_msgs::Marker>("path",1);
    visualization_msgs::Marker &path;
    path.header.frame_id = "planner";
    path.header.stamp = ros::Time::now();
    path.ns = "path";
    path.action = visualization_msgs::Marker::ADD;
    path.id = 0;
    path.type = visualization_msgs::Marker::LINE_STRIP;
    path.scale.x = 1;
    path.color.r = 0.2f;
    path.color.g = 0.2f;
    path.color.b = 1.0f;
    path.color.a = 1.0f;
    if (client.call(srv)){
        path.points = srv.response.path.PoseStamped
        path_pub.publish(path);
    }
    return 0;
}