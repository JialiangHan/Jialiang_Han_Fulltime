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
  CollisionDetection();

  /*!
     \brief evaluates whether the configuration is safe
     \return true if it is traversable, else false
  */
  bool isTraversable(const Node3D* node) const {
    /* Depending on the used collision checking mechanism this needs to be adjusted
       standard: collision checking using the spatial occupancy enumeration
       other: collision checking using the 2d costmap and the navigation stack
    */
    int x;
    int y;
    int t;
    // assign values to the configuration
    getConfiguration(node, x, y, t);

    int index;
    index = x * grid.info.width + y ;
    int threshhold;
    threshhold = 50;
    if (grid.data[index] > threshhold;){
        return false;
    }
    else {return true;}

  }

  void getConfiguration(const Node3D* node, float& x, float& y, float& t) {
      x = node->getX();
      y = node->getY();
      t = node->getT();
}
  /*!
     \brief updates the grid with the world map
  */
  void updateGrid(nav_msgs::OccupancyGrid::Ptr map) {grid = map;}

 private:
  /// The occupancy grid
  nav_msgs::OccupancyGrid::Ptr grid;
};
}
#endif // COLLISIONDETECTION_H
