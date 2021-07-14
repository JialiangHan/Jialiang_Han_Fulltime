#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include "planner.h"

using namespace planner;

int main(int argc, char **argv){

    ros::init(argc, argv, "test_a_star");

    ros::NodeHandle n("~");
    geometry_msgs::PoseStamped goal;
    goal.pose.position.x = 3;
    goal.pose.position.y=3;
    goal.pose.position.z=0;
    string agent_name = "agent_1";
    Planner pl(agent_name,goal);
    pl.plan();
    ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);
    nav_msgs::Path path;
    path = pl.get_path();
    while(ros::ok()){
        path_pub.publish(path);
        // path_pub.publish(pl.get_path());
        ros::spinOnce();
    }

    // ros::spin();
    return 0;
}