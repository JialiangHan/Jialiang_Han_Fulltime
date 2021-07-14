#ifndef NODE3D_H
#define NODE3D_H

#include <cmath>

namespace planner{
    /* a 3-D node (x,y,theta), actually, in this application, theta is always zero.
    */
    class Node3D {
       public:
       //default Node3D
       Node3D():Node3D(0,0,0,0,0,nullptr) {}
       // cost so far: cost from initial node to current node
       // cost to go: distance from current node to goal node
       Node3D(int x, int y,int theta, float cost_so_far, float cost_to_go,const Node3D* predecessor){
           this->x = x;
           this->y = y;
           this->theta = theta;
           this->cost_so_far = cost_so_far;
           this->cost_to_go = cost_to_go;
           this->predecessor = predecessor;
           this->in_openlist = false;
           this->in_closelist = false;
           this->index = -1;
       }
       //getter methods
       int get_x() const { return x;}
       int get_y() const { return y;}
       int get_theta() const { return theta;}
       float get_cost_so_far() const { return cost_so_far;}
       float get_cost_to_go() const { return cost_to_go;}
       float get_total_cost() const { return cost_so_far + cost_to_go;}
       int get_index() const { return index;}
       bool is_open() const { return in_openlist;}
       bool is_closed() const { return in_closelist;}
       const Node3D* get_predecessor() const { return predecessor;}

       //setter methods
       void set_x(const int& x) { this->x = x;}
       void set_y(const int& y) { this->y = y;}
       void set_theta(const int& theta) {this->theta = theta;}
       void set_cost_so_far(const float& cost_so_far) {this->cost_so_far = cost_so_far;}
       void set_cost_to_go(const float& cost_to_go) {this->cost_to_go = cost_to_go;}
       int set_index(int width) { this->index = y * width +x; return index;}
       // put node into openlist
       void open() {in_openlist = true; in_closelist =false;}
       // put node into closelist
       void close() {in_openlist = false; in_closelist = true;}
       // set node neither open nor closed
       void reset() {in_openlist = false; in_closelist = false;}
       //set predecessor
       void set_predecessor(const Node3D* predecessor) {this->predecessor = predecessor;}

       // udpate cost so far from its predecessor
       void update_cost_so_far() { cost_so_far = cost_so_far + movement_cost(*predecessor);}
       void update_cost_to_go(const Node3D& goal) {cost_to_go = movement_cost(goal);}
       float movement_cost(const Node3D& predecessor) const { return 10 * sqrt((x-predecessor.x)*(x-predecessor.x) + (y-predecessor.y)*(y-predecessor.y));}

       // node are equal if x,y, and theta are equal
       bool operator == (const Node3D& rhs) const;
        
       // GRID CHECKING
       /// Validity check to test, whether the node is in the 3D array.
       bool is_on_grid(const int width, const int height) const;

       // find its successor
       Node3D* create_successor(const int i);

       //constant values
       //number of movement direction, delta x, delta y and delta theta
       static const int dir;
       static const int dx[];
       static const int dy[];
       static const int dtheta[];

       private:
       int x;
       int y;
       int theta;
       float cost_so_far;
       float cost_to_go;
       int index;
       bool in_openlist;
       bool in_closelist;
       const Node3D* predecessor;
   };
}
#endif