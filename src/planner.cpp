// this file create an planner node
// subscribler topic: agent_feedback to get current position of agent
// subscrible grid map to get map info
// service client: get_plan

#include "planner.h"

using namespace planner;

Planner::Planner (string agent_name, geometry_msgs::PoseStamped end) {
    // subscribe map info
    subMap = n.subscribe("/grid_map",1, &Planner::setMap, this);
    string agent_feedback = "/"+agent_name + "/agent_feedback";
    subStart = n.subscribe(agent_feedback,1, &Planner::setStart,this);
    goal = end;
    service = n.advertiseService("get_plan",&Planner::get_plan,this);
};

bool Planner::get_plan(jialiang_han_fulltime::GetPlan::Request &req, jialiang_han_fulltime::GetPlan::Response &res){
    Planner planner(req.agent_name, req.goal);
    planner.plan();
    res.path = planner.get_path();
    return true;
}

void Planner::setMap(const nav_msgs::OccupancyGrid::Ptr map){
    grid = map;
}

void Planner::setStart(const geometry_msgs::PoseStamped::ConstPtr& current_position){
    start = *current_position;
}

nav_msgs::Path Planner::call_service(){
    client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
    jialiang_han_fulltime::GetPlan srv;
    srv.request.agent_name = agent_name;
    srv.request.goal = goal;
//    client.call(srv);
    if (ros::service::call("get_plan",srv)){
        return srv.response.path;
    }
    else{return path.get_path();}
}

void Planner::plan(){
    // int width = grid->info.width;
    // int height = grid->info.height;
    int width =10;
    int height =10;
    Node3D* nodes3D = new Node3D[width*height]();

    // retrieving goal position
    int x = goal.pose.position.x ;
    int y = goal.pose.position.y ;

    const Node3D nGoal(x, y, 0, 0, 0, nullptr);

    // retrieving start position
    x = start.pose.position.x ;
    y = start.pose.position.y ;
    Node3D nStart(x, y, 0, 0, 0, nullptr);
    // // check if start and goal exist in the path dict
    // if (path.check_path(nStart, nGoal)) {
    //     path.get_path_from_dict(nStart, nGoal);
    //     path.update_path_dict();
    //     path.publishPath();
    // }

    // else {
        // CLEAR THE PATH
        path.clear();
        // find goal node
        Node3D* solution = astar.path_planner(nStart,nGoal,nodes3D, width,height);
        // trace its parent and put it into a path list(vector)
        astar.trace_path(solution);
        path.update_path(astar.get_path());
        path.publishPath();
    // }
    delete [] nodes3D;
}
