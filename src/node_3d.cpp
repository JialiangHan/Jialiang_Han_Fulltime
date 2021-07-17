#include "node_3d.h"

using namespace planner;

// only allow agent to go left,right, up,down
const int Node3D::dir = 4;
const int Node3D::dx[] = { -1, 1, 0, 0 };
const int Node3D::dy[] = { 0, 0, -1, 1 };
const int Node3D::dtheta[] = { 0, 0, 0, 0 };

// check if node is on grid
bool Node3D::is_on_grid(const int width, const int height) const
{
  return x >= 0 && x <= width && y >= 0 && y <= height;
}

// create successor
Node3D* Node3D::create_successor(const int i)
{
  int x_successor;
  int y_successor;
  int theta_successor;

  x_successor = x + Node3D::dx[i];
  y_successor = y + Node3D::dy[i];
  theta_successor = theta + Node3D::dtheta[i];

  return new Node3D(x_successor, y_successor, theta_successor, cost_so_far, 0, this);
}

// node comparison
bool Node3D::operator==(const Node3D& rhs) const
{
  return x == rhs.x && y == rhs.y && theta == rhs.theta;
}