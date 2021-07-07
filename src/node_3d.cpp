##include "node_3d.h"

using namespace Planner;

// only allow agent to go left,right, up,down
const int Node3D::dir = 4;
const int Node3D::dx[] = {-1,1,0,0};
const int Node3D::dy[] = {0,0,-1,1};
const int Node3D::dtheta[] = {0,0,0,0};

//create successor
Node3D* Node3D::create_successor(cosnt int i) {
    int x_successor;
    int y_successor;
    int theta_successor;

    x_successor = x + Node3D::dx[i];
    y_successor = y + Node3D::dy[i];
    theta_successor = theta + Node3D::dtheta[i];

    return new Node3D(x_successor,y_successor,theta_successor,cost_so_far,0,this);
}

// node comparison
bool Node3D::operator ==(const Node3D& rhs) const {
    return x == rhs.x && y == rhs.y && theta == rhs.theta;
}