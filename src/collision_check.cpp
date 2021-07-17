
#include "collision_check.h"

namespace planner
{
bool CollisionDetection::isTraversable(const Node3D* node)
{
  /* Depending on the used collision checking mechanism this needs to be adjusted
     standard: collision checking using the spatial occupancy enumeration
     other: collision checking using the 2d costmap and the navigation stack
  */
  int x;
  int y;
  int t;
  // assign values to the configuration
  CollisionDetection::getConfiguration(node, x, y, t);

  int index;
  index = x * grid->info.width + y;
  int threshhold;
  threshhold = 50;
  if (grid->data[index] > threshhold)
  {
    return false;
  }
  else
  {
    return true;
  }
}
}  // namespace planner