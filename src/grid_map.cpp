// this file create a grid map publisher

#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>

// void position_callback_1(const geometry_msgs::PoseStamped msg)
// {

//     map.header.frame_id = "planner";
//     map.header.stamp = ros::Time::now();
//     map.info.resolution = 1; // unit is meter
//     map.info.width = 10; //unit is meter
//     map.info.height = 10; //unit is meter

//     int p[map.info.width*map.info.height] = {0}; //value here should be [0,100] is the probality
//     std::vector<signed char> a(p,p+100);
//     map.data = a;
//     map.data[msg.pose.position.x * map.info.width + msg.pose.position.y] = 1;
// }

// void position_callback_1(const geometry_msgs::PoseStamped msg)
// {

//     map.header.frame_id = "planner";
//     map.header.stamp = ros::Time::now();
//     map.info.resolution = 1; // unit is meter
//     map.info.width = 10; //unit is meter
//     map.info.height = 10; //unit is meter

//     int p[map.info.width*map.info.height] = {0}; //value here should be [0,100] is the probality
//     std::vector<signed char> a(p,p+100);
//     map.data = a;
//     map.data[msg.pose.position.x * map.info.width + msg.pose.position.y] = 1;
// }

int main(int argc, char** argv)
{
  ros::init(argc, argv, "grid_map");

  ros::NodeHandle n;

  ros::Publisher pub = n.advertise<nav_msgs::OccupancyGrid>("grid_map", 1);

  nav_msgs::OccupancyGrid map;
  // // subscribe agent position
  // ros::Subscriber agent_1_sub = n.subscribe("/agent_1/agent_feedback",1, position_callback_1);
  // ros::Subscriber agent_2_sub = n.subscribe("/agent_2/agent_feedback",1, position_callback_2);
  map.header.frame_id = "planner";
  map.header.stamp = ros::Time::now();
  map.info.resolution = 1;  // unit is meter
  map.info.width = 10;      // unit is meter
  map.info.height = 10;     // unit is meter

  int p[map.info.width * map.info.height] = { 0 };  // value here should be [0,100] is the probality
  std::vector<signed char> a(p, p + 100);
  map.data = a;

  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    pub.publish(map);
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}