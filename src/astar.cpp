#include "node_3d.h"
#include "astar.h"

using namespace planner;

Node3D* Astar::path_planner(Node3D& start, const Node3D& goal, Node3D* nodes3D, int width,int height){
    int index_predecessor, index_successor;
    float new_cost_so_far;

    start.update_cost_to_go(goal);
    start.open();
    openlist.push(&start);
    index_predecessor = start.get_index();
    nodes3D[index_predecessor] = start;
    
    Node3D* current_node;
    Node3D* successor;

    while (!openlist.empty()){
        current_node = openlist.top();
        index_predecessor =current_node->set_index(width);

        if (nodes3D[index_predecessor].is_closed()){
            openlist.pop();
            continue;
        }
        else if (nodes3D[index_predecessor].is_open()){
            nodes3D[index_predecessor].close();
            openlist.pop();

            //goal test
            if (*current_node==goal){
                return current_node;
            }
            else {
                for (int i = 0; i<Node3D::dir; i++){
                    //find successor of current node
                    successor = current_node->create_successor(i);
                    index_successor = successor->set_index(width);

                    if (!successor.isClosed() ){
                        successor->update_cost_so_far;
                        new_cost_so_far = successor->get_cost_so_far;

                        // if successor is not in open list or successor has a lower cost so far value, then put it into openlsit
                        if (!nodes3D[index_successor].isOpen() || new_cost_so_far < nodes3D[index_successor].get_cost_so_far()){
                            successor->update_cost_to_go(goal);
                            successor->open();
                            nodes3D[index_successor] = *successor;
                            openlist.push(&nodes3D[index_successor]);
                            delete successor;
                        }
                        else {delete successor;}
                    }
                    else {delete successor;}
                }
            }
        }
    }
    if (openlist.empty()) {
        return nullptr;
    }
    return nullptr;
}

void Astar::get_path(Node3D* goal){
    path.clear();

    Node3D* current_node = goal;
    while (!current_node != NULL){
        path.push_back(current_node);
        current_node = current_node->get_predecessor();
    }
}