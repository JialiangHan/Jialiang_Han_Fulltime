#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_planner");

    ros::NodeHandle nh("~");
    
    geometry_msgs::PoseStamped goal;
    goal.pose.position.x = 8;
    goal.pose.position.y = 8;
    goal.pose.position.z = 0;
    
    Planner plan("agent_1",goal);
    // plan.set_get_plan_server();    

    nav_msgs::Path nav_path;

    ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("path",1);

    ros::Rate loop_rate(10);
    
    nav_path = plan.call_service("agent_1",goal);

    while(ros::ok()){
        path_pub.publish(nav_path);
        ros::spinOnce;
        // path_pub.publish(pl.get_path());
        loop_rate.sleep();
    }

    // ros::spin();
    return 0;
}