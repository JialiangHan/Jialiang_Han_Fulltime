/* this path file is to
    store path for future use
    transfer path from vector to nav msgs for visualization
*/
#ifndef PATH_H
#define PATH_H

#include <cstring>
#include <vector>
#include <map>

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "node3d.h"

namespace planner {

class Path {
 public:
  /// The default constructor initializing the path object and setting publishers for the same.
  Path() {
    std::string pathTopic = "/path";
    }

    // TOPICS TO PUBLISH
    pubPath = n.advertise<nav_msgs::Path>(pathTopic, 1);

    // CONFIGURE THE CONTAINER
    path.header.frame_id = "path";
  }
  // check if path exist for this start and goal
  bool check_path(Node3D& start, const Node3D& goal);
  // get path list from dict
  void get_path_from_dict(Node3D& start, const Node3D& goal);
  // transfer path from vector form into a nav_msgs path
  void update_Path(const vector<Node3D> &nodePath);
  // add node to nav::msgs/Path
  void addSegment(const Node3D& node);
  /// return path got from astar
  nav_msgs::Path get_path() {return path};

  /// Clears the path
  void clear();
  /// Publishes the path
  void publishPath() { pubPath.publish(path); }

 private:
  /// A handle to the ROS node
  ros::NodeHandle n;
  /// Publisher for the path as a spline
  ros::Publisher pubPath;
  nav_msgs::Path path;
  /// a dict to store path
  map<vector<Node3D>, vector<Node3D>> path_dict;
  /// a vector contains path lits
  vector<Node3D> path_list;

};
}
#endif // PATH_H
