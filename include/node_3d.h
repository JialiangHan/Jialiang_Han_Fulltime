#ifndef NODE3D_H
#define NODE3D_H

#include <cmath>

namespace Planner{
    /* a 3-D node (x,y,theta), actually, in this application, theta is always zero.
    */
   class Node3D{
       public:
       //default Node3D
       Node3D():Node3D(0,0,0,0,0,nullptr) {}
       // cost so far: cost from initial node to current node
       // cost to go: distance from current node to goal node
       Node3D(float x, float y,float theta, float cost_so_far, float cost_to_go, const Node3D* predecessor){
           this->x = x;
           this->y = y;
           this->theta = theta;
           this->cost_so_far = cost_so_far;
           this->cost_to_go = cost_to_go;
           this->predecessor = predecessor;
           this->in_openlist = false;
           this->in_closelist = false;
       }
       //getter methods
       float get_x() const { return x;}
       float get_y() const { return y;}
       float get_theta() const { return theta;}
       float get_cost_so_far() const { return cost_so_far;}
       float get_cost_to_go() const { return cost_to_go;}
       float get_total_cost() const { return cost_so_far + cost_to_go;}
       bool is_open() const { return in_openlist;}
       bool is_closed() const { return in_closelist;}
       const Node3D* get_predecessor() const { return predecessor;}

       //setter methods
       void set_x(const float& x) { this->x = x;}
       void set_y(const float& y) { this->y = y;}
       void set_theta(const float& theta) {this->theta = theta;}
       
   }
}