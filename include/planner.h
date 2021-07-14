#ifndef PLANNER_H
#define PLANNER_H

#include <string.h>
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>
#include <jialiang_han_fulltime/GetPlan.h>
#include "astar.h"
#include "node_3d.h"
#include "path.h"

namespace planner {

class Planner {
 public:
  /// The default constructor
  // Planner();
  Planner(std::string agent_name, geometry_msgs::PoseStamped goal);
  // {
  //     this->agent_name=agent_name;
  //     this->goal = goal;
  // };


  // a callback function to set map size
  void setMap(const nav_msgs::OccupancyGrid map);

  // a callback function to set start node
  void setStart(const geometry_msgs::PoseStamped start);

  // a callback function to set goal node
  void setGoal(const geometry_msgs::PoseStamped goal);

  // main path planning function
  void plan();
  // return path in nav::msgs/path format
  nav_msgs::Path get_path(){ return path.get_path();}
  /// function for service get plan
  bool get_plan(jialiang_han_fulltime::GetPlan::Request &req, jialiang_han_fulltime::GetPlan::Response &res);
  /// this function call get plan service
  nav_msgs::Path call_service(std::string name, geometry_msgs::PoseStamped point);

 private:
  /// The node handle
  ros::NodeHandle n;
  /// A service server to get plan
  ros::ServiceServer service;
  ros::ServiceClient client;
  /// A subscriber for receiving map updates
  ros::Subscriber subMap;
  /// A subscriber for receiving start updates: current position of agent
  ros::Subscriber subStart;
  /// A publisher for publish path to rviz
  ros::Publisher path_pub;
  /// A pointer to the grid the planner runs on
  nav_msgs::OccupancyGrid grid;
  /// The start pose set through RViz
  geometry_msgs::PoseStamped start;
  /// The goal pose set through RViz
  geometry_msgs::PoseStamped goal;
  /// agent name
  std::string agent_name;
  Path path;
  Astar astar;
};
}
#endif // PLANNER_H
