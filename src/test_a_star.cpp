#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"
#include "astar.h"
#include "path.h"

using namespace planner;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "test_a_star");

  ros::NodeHandle n("~");
  // test astar.cpp
  int width = 10;
  int height = 10;
  Node3D* nodes3D = new Node3D[width * height]();
  // retrieving goal position
  int x = 2;
  int y = 0;
  const Node3D nGoal(x, y, 0, 0, 0, nullptr);
  // retrieving start position
  x = 0;
  y = 8;
  Node3D nStart(x, y, 0, 0, 0, nullptr);
  // CLEAR THE PATH
  Astar astar;
  vector<Node3D> path;
  path = astar.get_path();
  delete[] nodes3D;
  Path transfer;
  transfer.update_path(path);
  nav_msgs::Path nav_path;
  nav_path = transfer.get_path();
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path", 1);
  while (ros::ok())
  {
    path_pub.publish(nav_path);
    ros::spinOnce();
  }

  // ros::spin();
  return 0;
}