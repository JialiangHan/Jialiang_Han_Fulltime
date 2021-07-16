#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "astar.h"
#include "path.h"
#include "collision_check.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_path");

    ros::NodeHandle n;
    // test path.cpp using results from astar.cpp
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
    // nav_msgs::OccupancyGrid map;
    // map.header.frame_id = "planner";
    // map.header.stamp = ros::Time::now();
    // map.info.resolution = 1; // unit is meter
    // map.info.width = 10; //unit is meter
    // map.info.height = 10; //unit is meter
    // int p[map.info.width*map.info.height] = {0}; //value here should be [0,100] is the probality
    // std::vector<signed char> a(p,p+100);
    // map.data = a;

    // CollisionDetection configuration;
    // configuration.updateGrid(map);
    // // find goal node
    // Node3D* solution = astar.path_planner(nStart,nGoal,nodes3D, configuration, width,height);
    // trace its parent and put it into a path list(vector)
    // astar.trace_path(solution);
    vector<Node3D> path;
    path = astar.get_path();
    delete [] nodes3D;
    Path transfer;
    transfer.clear();
    transfer.update_path(path);

    // transfer.publishPath();
    
    nav_msgs::Path nav_path;
    nav_path = transfer.get_path();
    ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);

    while(ros::ok()){
        path_pub.publish(nav_path);
        // path_pub.publish(pl.get_path());
        ros::spinOnce();
    }
    // this function is a must or spinOnce;
    ros::spin();
    return 0;
}