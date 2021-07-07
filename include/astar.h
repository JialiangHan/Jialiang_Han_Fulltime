##ifndef ASTAR_H
##define ASTAR_H

##include "node_3d.h"

namespace planner{
class Node3D;
class Astar{

public:
    // path planner using A star algorithm.
    //param start: start position
    //param goal: goal position
    //parm nodes3D: array of node 3D
    //width and height are from map info
    static Node3D* path_planner(Node3D& start, const Node3D& goal, Node3D* nodes3D, int width, int height);
    // get path from goal, put all its parents into path
    void get_path(Node3D* goal, vector<Node3D>& path);
}
}