//this file is a client for get plan
// purpose of this server is to get path from start to goal

#include <ros/ros.h>
#include <jialiang_han_fulltime/GetPlan.h>


int main(int argc, char **argv){
    ros::init(argc,argv,"get_plan_client");
    ros::NodeHandle n;

    ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");

    jialiang_han_fulltime::GetPlan srv;
    srv.request.start.pose.position.x = atoi(argv[1]);
    srv.request.start.pose.position.y = atoi(argv[2]);
    srv.request.start.pose.position.z = atoi(argv[3]);
    srv.request.goal.pose.position.x = atoi(argv[4]);
    srv.request.goal.pose.position.y = atoi(argv[5]);
    srv.request.goal.pose.position.z = atoi(argv[6]);
    srv.request.width= 10;
    srv.request.height= 10;

    ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);
    if(client.call(srv)){
        path_pub.publish(srv.response.path);
    } 
    return 0;
}