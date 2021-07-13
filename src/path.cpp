#include "path.h"

using namespace planner;


//###################################################
//                                         CLEAR PATH
//###################################################

void Path::clear() {
  Node3D node;
  path.poses.clear();
  publishPath();
}

// __________
// update path: transfer vector path to a nav::msgs path
void Path::update_path(const std::vector<Node3D>& nodePath) {
  path.header.stamp = ros::Time::now();

  for (size_t i = 0; i < nodePath.size(); ++i) {
    addSegment(nodePath[i]);
  }

  return;
}

// check if path exist for this start and goal
// bool Path::check_path(Node3D& start, const Node3D& goal){
//     std::vector<Node3D> start_end_point {start, goal};
//     if (path_dict.count(start_end_point) >0) {
//         return true;
//     }
//     else { return false;}
// }

// get path from dict
// void Path::get_path_from_dict(Node3D& start, const Node3D& goal){
//     std::vector<Node3D> start_end_point {start, goal};
//     path_list = path_dict[start_end_point];
// }
// update path using dict path
void Path::update_path_dict(){
  path.header.stamp = ros::Time::now();

  for (size_t i = 0; i < path_list.size(); ++i) {
    addSegment(path_list[i]);
  }

  return;
}
// ___________
// ADD SEGMENT
void Path::addSegment(const Node3D& node) {
  geometry_msgs::PoseStamped vertex;
  vertex.pose.position.x = node.get_x();
  vertex.pose.position.y = node.get_y() ;
  vertex.pose.position.z = 0;
  vertex.pose.orientation.x = 0;
  vertex.pose.orientation.y = 0;
  vertex.pose.orientation.z = 0;
  vertex.pose.orientation.w = 0;
  path.poses.push_back(vertex);
}