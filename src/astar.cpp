#include "node_3d.h"
#include "astar.h"
#include <queue>

namespace planner{

Node3D* Astar::path_planner(Node3D& start, const Node3D& goal,Node3D* nodes3D, CollisionDetection& configurationSpace,int width,int height){
    // set index of predecessor and successor
    int index_predecessor, index_successor;
    float new_cost_so_far;
    // reset the open and closed list
    for (int i = 0; i < width * height; ++i) {
        nodes3D[i].reset();
    }

    // define openlist as priority queue
    priority_queue< Node3D*, vector<Node3D*>, node_comparison> openlist;

    // update cost to go (heuristics) of start node
    start.update_cost_to_go(goal);
    // mark start node as open
    start.open();
    // put start node into openlist
    openlist.push(&start);
    // set index of predecessor equal to start node
    index_predecessor = start.set_index(width);
    // nodes3D is Node3D array 
    nodes3D[index_predecessor] = start;
    // pointer to current node and successor
    Node3D* current_node;
    Node3D* successor;
    // while openlist is not empty
    while (!openlist.empty()){
        // pop node with lowest total cost in the openlist
        current_node = openlist.top();
        index_predecessor =current_node->set_index(width);
        // if current node is in openlist
        if (nodes3D[index_predecessor].is_open()){
            // put current node into close list
            nodes3D[index_predecessor].close();
            // remove current node from open list
            openlist.pop();

            //goal test
            if (*current_node==goal){
                return current_node;
            }
            
            else {
                for (int i = 0; i<Node3D::dir; i++){
                    //find successor of current node
                    successor = current_node->create_successor(i);
                    // set index of successor
                    index_successor = successor->set_index(width);
                    // make sure successor is on the grid map and is not obstacle
                    if (successor->is_on_grid(width,height) && configurationSpace.isTraversable(nSucc) ){
                        // make sure successor is not in close list or has the same index as predecessor
                        if (!nodes3D[index_successor].is_closed() || index_predecessor ==index_successor ){
                            // update cost so far
                            successor->update_cost_so_far();
                            new_cost_so_far = successor->get_cost_so_far();

                        // if successor is not in open list or successor has a lower cost so far value, then put it into openlsit
                        if (!nodes3D[index_successor].is_open() || new_cost_so_far < nodes3D[index_successor].get_cost_so_far()||index_predecessor==index_successor){
                            //update cost to go
                            successor->update_cost_to_go(goal);
                            // put successor into openlist
                            successor->open();
                            nodes3D[index_successor] = *successor;
                            openlist.push(&nodes3D[index_successor]);
                            delete successor;
                        }
                        else {delete successor;}
                        }
                    } else {delete successor;}
                    
                }
            }
        }
    }
    if (openlist.empty()) {
        return nullptr;
    }
    return nullptr;
}

void Astar::trace_path(const Node3D* goal, vector<Node3D> path){
    if (goal == nullptr){
        this->path = path;
        return;
    }

    path.push_back(*goal);
    trace_path(goal->get_predecessor(),path);
}


}
