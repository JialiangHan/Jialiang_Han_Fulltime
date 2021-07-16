#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"
#include "astar.h"
#include "path.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_a_star");

    ros::NodeHandle n("~");
    // test astar.cpp
    int width =10;
    int height =10;
    Node3D* nodes3D = new Node3D[width*height]();
    // retrieving goal position
    int x =2 ;
    int y = 0 ;
    const Node3D nGoal(x, y, 0, 0, 0, nullptr);
    // retrieving start position
    x = 0 ;
    y = 8 ;
    Node3D nStart(x, y, 0, 0, 0, nullptr);
    // CLEAR THE PATH
    Astar astar;
    // find goal node
    // Node3D* solution = astar.path_planner(nStart,nGoal,nodes3D, width,height);
    // trace its parent and put it into a path list(vector)
    // astar.trace_path(solution);
    vector<Node3D> path;
    path = astar.get_path();
    // path.publishPath();
    delete [] nodes3D;
    // ros can`t publish vector<Node3D>, need to convert vector to nav msgs
    // ros::Publisher path_pub = n.advertise<vector<Node3D>>("path",1);
    Path transfer;
    transfer.update_path(path);
    nav_msgs::Path nav_path;
    nav_path = transfer.get_path();
    // geometry_msgs::PoseStamped goal;
    // goal.pose.position.x = 3;
    // goal.pose.position.y=3;
    // goal.pose.position.z=0;
    // string agent_name = "agent_1";
    // Planner pl(agent_name,goal);
    // pl.plan();
    ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);
    // nav_msgs::Path path;
    // path = pl.get_path();
    while(ros::ok()){
        path_pub.publish(nav_path);
        // path_pub.publish(pl.get_path());
        ros::spinOnce();
    }

    // ros::spin();
    return 0;
}