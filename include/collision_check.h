#ifndef COLLISIONDETECTION_H
#define COLLISIONDETECTION_H

#include <nav_msgs/OccupancyGrid.h>
#include "node_3d.h"

namespace planner {
/*!
   \brief The CollisionDetection class determines whether a given configuration q of the robot will result in a collision with the environment.

   It is supposed to return a boolean value that returns true for collisions and false in the case of a safe node.
*/
class CollisionDetection {
 public:
  /// Constructor
  CollisionDetection() {}

  /*!
     \brief evaluates whether the configuration is safe
     \return true if it is traversable, else false
  */
  bool isTraversable(const Node3D* node);

  void getConfiguration(const Node3D* node, int& x, int& y, int& t) {
      x = node->get_x();
      y = node->get_y();
      t = node->get_theta();
}
  /*!
     \brief updates the grid with the world map
  */
  void updateGrid(nav_msgs::OccupancyGrid::ConstPtr map) {grid = map;}

 private:
  /// The occupancy grid
  nav_msgs::OccupancyGrid::ConstPtr grid;
};
}
#endif // COLLISIONDETECTION_H
