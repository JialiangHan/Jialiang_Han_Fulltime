/* this file define structure Key and KeyHasher for unordered_map
*/
#include "node_3d.h"
#include <functional>

namespace planner{
    struct Key
    {
      Node3D& start;
      const Node3D& goal;

      bool operator==(const Key &other) const
      { return (start == other.start
                && goal == other.goal);
      }
    };

    struct KeyHasher
    {
      std::size_t operator()(const Key& k) const
      {
        using std::size_t;
        using std::hash;

        size_t h1 = hash<int>()(k.start.get_x());
        size_t h2 = hash<int>()(k.start.get_y());
        size_t h3 = hash<int>()(k.start.get_theta());
        size_t h4 = hash<int>()(k.goal.get_x());
        size_t h5 = hash<int>()(k.goal.get_y());
        size_t h6 = hash<int>()(k.goal.get_theta());
        size_t res = 17;
        res = res *31 + h1;
        res = res *31 + h2;
        res = res *31 + h3;
        res = res *31 + h4;
        res = res *31 + h5;
        res = res *31 + h6;

        return res;
      }
    };
}