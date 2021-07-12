#ifndef ASTAR_H
#define ASTAR_H

#include "node_3d.h"
#include <vector>
#include <queue>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <unordered_map>

using namespace std;

namespace planner{
class Node3D;

struct node_comparison{
    bool operator() (const Node3D* lhs, const Node3D* rhs) const {
        return lhs->get_total_cost() > rhs->get_total_cost();
    }
};

class Astar{

public:
    Astar() {}
    // path planner using A star algorithm.
    //param start: start position
    //param goal: goal position
    //parm nodes3D: array of node 3D
    //width and height are from map info
    Node3D* path_planner(Node3D& start, Node3D& goal, int width, int height);
    // get path from goal, put all its parents into path
    void get_path(Node3D* goal,vector<Node3D*> pathlist);
    //this function use geometry msg posestamped as input and output is nav msgs path.
    nav_msgs::Path planning(geometry_msgs::PoseStamped start, geometry_msgs::PoseStamped goal, int width, int height);


private:
    priority_queue< Node3D*, vector<Node3D*>, node_comparison> openlist;
    unordered_map<int, Node3D> OpenDict; 
    vector<Node3D*> pathlist;
};
}
#endif