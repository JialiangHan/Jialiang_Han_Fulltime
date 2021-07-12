// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// subscrible grid map to get map info
// service client: get_plan

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/OccupancyGrid.h>
#include <map>
#include <jialiang_han_fulltime/GetPlan.h>
#include "astar.h"
#include "node_3d.h"
#include "planner.h"

using namespace planner;

Planner::Planner(agent_name, end){
    // subscribe map info
    subMap = n.subscribe("/grid_map",1, &Planner::setMap, this);
    string agent_feedback = "/"+agent_name + "/agent_feedback";
    subStart = n.subscribe(agent_feedback,1, &Planner::setStart,this);
    goal = end;
}


void Planner::setMap(const nav::msgs::OccupancyGrid::Ptr map){
    grid = map;
}

void Planner::setStart(const geometry_msgs::PoseStamped::ConstPtr& current_position){
    start = *current_position;
}

void plan(){
    int width = grid->info.width;
    int height = grid->info.height;
    Node3D* nodes3D = new Node3D[width*height]();

    // retrieving goal position
    int x = goal.pose.position.x ;
    int y = goal.pose.position.y ;

    const Node3D nGoal(x, y, 0, 0, 0, nullptr);
_______________________
    // retrieving start position
    x = start.pose.pose.position.x ;
    y = start.pose.pose.position.y ;
    Node3D nStart(x, y, 0, 0, 0, nullptr);

    Node3D* solution = Astar::path_planner(nStart,nGoal,nodes3D, width,height);
    Astar::trace_path();
    

}
int width;
int height;
geometry_msgs::PoseStamped current_position;

void map_callback(nav_msgs::OccupancyGrid msg){
    width = msg.info.width;
    height = msg.info.height;
}

void agent_feedback_callback(geometry_msgs::PoseStamped msg){
    current_position = msg;
}

int main(int argc,char **argv){

    ros::init(argc, argv, "planner");

    ros::NodeHandle n;
    // subscribe map info
    ros::Subscriber map_sub = n.subscribe("grid_map", 1, map_callback);
    // subscribe agent current postion
    string agent_name;
    agent_name = argv[1];
    string topic_name;
    // get topic name of specific agent
    topic_name = agent_name + "/agent_feedback";
    ros::Subscriber agent_feedback_sub = n.subscribe(topic_name, 1, agent_feedback_callback);
    //call get plan service
    ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
    jialiang_han_fulltime::GetPlan srv;
    // convert argv[2]，argv[3],argv[4] into geometry_msgs::PoseStamped
    srv.request.goal.pose.position.x = atoi(argv[2]);
    srv.request.goal.pose.position.y = atoi(argv[3]);
    srv.request.goal.pose.position.z = atoi(argv[4]);
    // publish path to rviz
    ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);
    
    ros::Rate loop_rate(0.5);

    while (ros::ok()){
        ros::spinOnce();
        srv.request.start = current_position;
        srv.request.width = width;
        srv.request.height = height;
        client.call(srv);
        path_pub.publish(srv.response.path);
        
        loop_rate.sleep();
    }
    return 0;
}