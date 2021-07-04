#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <nav_msgs/OccupancyGrid.h>


nav_msgs::OccupancyGridPtr grid;

void map_callback(const nav_msgs::OccupancyGrid::Ptr map){
    grid = map;
}

int main(int argc, char** argv){
    ros::init(argc,argv,"tf_broadcaster");
    ros::NodeHandle n;

    ros::Subscriber map = n.subscribe("grid_map", 1, map_callback);
    tf::Pose tfPose;

    ros::Rate loop_rate(0.5);
    tf::TransformBroadcaster broadcaster;

    while (ros::ok()){
        
    }
}