#ifndef PLANNER_H
#define PLANNER_H


#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <geometry_msgs/PoseStamped.h>

#include "atar.h"
#include "node_3d.h"


namespace planner {
/*!
   \brief A class that creates the interface for the hybrid A* algorithm.

    It inherits from `ros::nav_core::BaseGlobalPlanner` so that it can easily be used with the ROS navigation stack
   \todo make it actually inherit from nav_core::BaseGlobalPlanner
*/
class Planner {
 public:
  /// The default constructor
  Planner();
  Planner(string agent_name, geometry_msgs::PoseStamped goal){
      this->agent_name=agent_name;
      this->goal = goal;
  };


  /*!
     \brief Sets the map e.g. through a callback from a subscriber listening to map updates.
     \param map the map or occupancy grid
  */
  void setMap(const nav_msgs::OccupancyGrid::Ptr map);

  /*!
     \brief setStart
     \param start the start pose
  */
  void setStart(const geometry_msgs::PoseStamped::ConstPtr& start);

  /*!
     \brief setGoal
     \param goal the goal pose
  */
  void setGoal(const geometry_msgs::PoseStamped::ConstPtr& goal);

  /*!
     \brief The central function entry point making the necessary preparations to start the planning.
  */
  void plan();

 private:
  /// The node handle
  ros::NodeHandle n;
  /// A subscriber for receiving map updates
  ros::Subscriber subMap;
  /// A subscriber for receiving start updates: current position of agent
  ros::Subscriber subStart;
  /// A publisher for publish path to rviz
  ros::Publisher path_pub;
  /// A pointer to the grid the planner runs on
  nav_msgs::OccupancyGrid::Ptr grid;
  /// The start pose set through RViz
  geometry_msgs::PoseStamped start;
  /// The goal pose set through RViz
  geometry_msgs::PoseStamped goal;
  /// agent name
  string agent_name;

};
}
#endif // PLANNER_H
