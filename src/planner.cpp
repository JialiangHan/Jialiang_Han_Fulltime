// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// service client: get_plan

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "astar.h"
#include "node_3d.h"

using namespace planner;

int main(int argc,char **argv){

    ros::init(argc, argv, "planner");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<visualization_msgs::Marker>("path",1);
    visualization_msgs::Marker marker;
    marker.header.frame_id = "planner";
    marker.header.stamp = ros::Time::now();
    marker.ns = "marker";
    marker.id = 0;
    marker.type =  visualization_msgs::Marker::LINE_STRIP;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose = current_position.pose; 
    marker.scale.x = 1;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0; 

    vector<Node3D*> path;

    Node3D* solution = Astar::path_planner();
    Astar::get_path(solution,path);

    while (ros::ok()){
        convert_path_to_marker(path,marker);
        pub.publish(marker);
    }

    ros::shutdown();
    return 0;
}