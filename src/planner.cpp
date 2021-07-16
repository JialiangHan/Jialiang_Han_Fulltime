// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// subscrible grid map to get map info
// service client: get_plan
#include <ros/ros.h>
// #include <ros/callback_queue.h>
#include "planner.h"
#include <iostream>
#include <string>


using namespace planner;

Planner::Planner (std::string agent_name, geometry_msgs::PoseStamped end) {
    goal = end;
    // ros::CallbackQueue my_callback_queue;
    // n.setCallbackQueue(&my_callback_queue);
    // subscribe map info
    subMap = n.subscribe("/grid_map", 500, &Planner::setMap, this);
    // my_callback_queue.callOne(ros::WallDuration(0));
    string topic_name;
    if (agent_name == "agent_1"){
        topic_name = "/agent_1/agent_feedback";
    }
    if (agent_name == "agent_2"){
        topic_name = "/agent_2/agent_feedback";
    }
    subStart = n.subscribe(topic_name, 500, &Planner::setStart,this);
    // my_callback_queue.callOne(ros::WallDuration(0));
    // set server for get_plan service
    // todo: maybe i can set another function to set service server
    // service = n.advertiseService("get_plan",&Planner::get_plan,this);
    // my_callback_queue.callOne(ros::WallDuration(0));
    // ros::spinOnce();
    ros::Rate loop_rate(10);
    int i =0;
    while(ros::ok()&& i<=5){
        ros::spinOnce();
        loop_rate.sleep();
        i++;
    }
};

bool Planner::get_plan(jialiang_han_fulltime::GetPlan::Request &req, jialiang_han_fulltime::GetPlan::Response &res){
//    Planner planner(req.agent_name, req.goal);
    Planner::plan();
    res.path = Planner::get_path();
    // ros::spin();
    return true;
}

void Planner::setMap(const nav_msgs::OccupancyGrid::ConstPtr& map){
    grid = *map;
    configurationSpace.updateGrid(map);
}

void Planner::setStart(const geometry_msgs::PoseStamped::ConstPtr& current_position){
    start = *current_position;
}

nav_msgs::Path Planner::call_service(std::string name, geometry_msgs::PoseStamped point){
    // todo: here client and server are on the same Nodehandle, maybe a correction is to create a new Nodehandle for client
    client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
    jialiang_han_fulltime::GetPlan srv;
    srv.request.agent_name = name;
    srv.request.goal = point;
    client.call(srv);
    // ros::service::call("get_plan",srv);
    return srv.response.path;
    // }
    // else{return path.get_path();}
}

void Planner::plan(){
    //  int width = grid.info.width;
    //  int height = grid.info.height;
    int width =10;
    int height =10;
    if (grid.info.width!=0){
        width = grid.info.width;
    }
    if (grid.info.height!=0){
        height = grid.info.height;
    }
    Node3D* nodes3D = new Node3D[width * height]();

    // retrieving goal position
    int x = goal.pose.position.x ;
    int y = goal.pose.position.y ;

    const Node3D nGoal(x, y, 0, 0, 0, nullptr);

    // retrieving start position
    x = start.pose.position.x ;
    y = start.pose.position.y ;
    // if (x==0){
    //     x = grid.info.width;
    // }
    // if (y==0){
    //     height = grid.info.height;
    // }
    Node3D nStart(x, y, 0, 0, 0, nullptr);
     // check if start and goal exist in the path dict
     if (path.check_path(nStart, nGoal)) {
         path.get_path_from_dict(nStart, nGoal);
         path.update_path_dict();
//         path.publishPath();
     }

     else {
        // CLEAR THE PATH
        path.clear();
        // find goal node
        Node3D* solution = astar.path_planner(nStart,nGoal,nodes3D, configurationSpace, width,height);
        // trace its parent and put it into a path list(vector)
        astar.trace_path(solution);
        path.update_path(astar.get_path());
        // path.publishPath();
     }
    delete [] nodes3D;
}
