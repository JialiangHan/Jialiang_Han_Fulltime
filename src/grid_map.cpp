// this file create a grid map publisher

#include "ros/ros.h"
#include "nav_msgs/OccupancyGrid.h"

int main(int argc,char **argv){

    ros::init(argc, argv, "grid_map");

    ros::NodeHandle n;

    ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("grid_map",1);
    nav_msgs::OccupancyGrid map;

    map.header.frame_id = "map";
    map.header.stamp = ros::Time::now();
    map.info.resolution = 1; // unit is meter
    map.info.width = 10; //unit is meter
    map.info.height = 10; //unit is meter

    int p[map.info.width*map.info.height] = {0}; //value here should be [0,100] is the probality
    std::vector<signed char> a(p,p+100);
    map.data = a;

    while (ros::ok()){
        pub.publish(map);
    }

    ros::shutdown();
    return 0;
}