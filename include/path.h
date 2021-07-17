/* this path file is to
    store path for future use
    transfer path from vector to nav msgs for visualization
*/
#ifndef PATH_H
#define PATH_H

#include <cstring>
#include <vector>
#include <unordered_map>

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "node_3d.h"
#include "key_hash.h"

using namespace std;

namespace planner
{
class Path
{
public:
  /// The default constructor initializing the path object and setting publishers for the same.
  Path()
  {
    std::string pathTopic = "/path";
    // CONFIGURE THE CONTAINER
    path.header.frame_id = "planner";
  }
  // check if path exist for this start and goal
  bool check_path(Node3D& start, const Node3D& goal);
  // get path list from dict
  void get_path_from_dict(Node3D& start, const Node3D& goal);
  void update_path_dict();
  // transfer path from vector form into a nav_msgs path
  void update_path(const std::vector<Node3D>& nodePath);
  // add node to nav::msgs/Path
  void addSegment(const Node3D& node);
  /// return path got from astar
  nav_msgs::Path get_path()
  {
    return path;
  }

  /// Clears the path
  void clear();

private:
  /// A handle to the ROS node
  ros::NodeHandle n;
  nav_msgs::Path path;
  /// a dict to store path
  unordered_map<Key, vector<Node3D>, KeyHasher> path_dict;
  /// a vector contains path lits
  vector<Node3D> path_list;
};
}  // namespace planner
#endif  // PATH_H
