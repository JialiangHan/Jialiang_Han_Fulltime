#ifndef ASTAR_H
#define ASTAR_H

#include "node_3d.h"
#include <vector>
#include <queue>

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
    static Node3D* path_planner(Node3D& start, const Node3D& goal, Node3D* nodes3D, int width, int height);
    // trace path from goal, put all its parents into path
    void trace_path(const Node3D* goal, vector<Node3D> path=vector<Node3D>());
    const vector<Node3D>& get_path(){return path;}

private:
    vector<Node3D> path;
};
}
#endif