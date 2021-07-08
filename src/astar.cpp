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

nav_msgs::Path* Astar::planning(geometry_msgs::PoseStamped& start, geometry_msgs::PoseStamped& goal, int width, int height){
    Node3D* nodes3D = new Node3D[width * height]();
    //convert start to node3D start
    float x_start = start.pose.position.x;
    float y_start = start.pose.position.y;
    float theta_start = start.pose.position.z;
    Node3D nstart(x_start,y_start,theta_start,0,0,nullptr);
    //convert goal to node3D goal
    float x_goal = goal.pose.position.x;
    float y_goal = goal.pose.position.y;
    float theta_goal = goal.pose.position.z;
    const Node3D ngoal(x_goal,y_goal,theta_goal,0,0,nullptr);
    
    //find path
    Node3D* solution = Astar::path_planner(nstart, ngoal, nodes3D, width, height);
    //get path in vector form
    Astar::get_path(solution);
    //convert vector path into nav msgs path
    nav_msgs::Path path;
    if (!pathlist.empty()){
        path.header.stamp = ros::Time::now();
        path.header.frame_id = "planner";
        path.poses.clear();
        for (int i=0; i<pathlist.size(); i++){
            geometry_msgs::Posestamped pose_stamped;
            pose_stamped.header.stamp = ros::Time::now();
            pose_stamped.header.frame_id = "planner";
            pose_stamped.pose.position.x = pathlist[i].get_x();
            pose_stamped.pose.position.y = pathlist[i].get_y();
            pose_stamped.pose.position.z = pathlist[i].get_theta();
            path.poses.push_back(pose_stamped);
        }
        return path;
    }

}