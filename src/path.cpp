#include "path.h"

using namespace planning;


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
bool check_path(Node3D& start, const Node3D& goal){
    vector<Node3D> start_end_point {start, goal};
    if path_dict.count(start_end_point) >0 {
        return true;
    }
    else { return false;}
}

// get path from dict
void get_path(Node3D& start, const Node3D& goal){
    vector<Node3D> start_end_point {start, goal};
    path_list = path_dict[start_end_point];
}
// ___________
// ADD SEGMENT
void Path::addSegment(const Node3D& node) {
  geometry_msgs::PoseStamped vertex;
  vertex.pose.position.x = node.getX();
  vertex.pose.position.y = node.getY() ;
  vertex.pose.position.z = 0;
  vertex.pose.orientation.x = 0;
  vertex.pose.orientation.y = 0;
  vertex.pose.orientation.z = 0;
  vertex.pose.orientation.w = 0;
  path.poses.push_back(vertex);
}