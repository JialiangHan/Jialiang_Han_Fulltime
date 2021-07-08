// this file create an agent node
// publish current position on topic "agent_feedback"
// a service "update_goal" to call planner for a path

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/PoseStamped.h>

int main(int argc,char **argv){

    ros::init(argc, argv, "agent");

    ros::NodeHandle n("~");

    int initial_position_x;
    int initial_position_y;
    int initial_position_theta;
    n.param<int>("x",initial_position_x, 0);
    n.param<int>("y",initial_position_y, 0);
    n.param<int>("theta",initial_position_theta, 0);
    
    ros::Publisher pub = n.advertise<geometry_msgs::PoseStamped>("agent_feedback",1);
    geometry_msgs::PoseStamped current_position;
        
    current_position.header.frame_id = "planner";
    current_position.header.stamp = ros::Time::now();
    current_position.pose.position.x = initial_position_x; // unit is meter
    current_position.pose.position.y = initial_position_y; //unit is meter
    current_position.pose.position.z = initial_position_theta; //unit is degree

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",1);   
    visualization_msgs::Marker marker;
    marker.header.frame_id = "planner";
    marker.header.stamp = ros::Time::now();
    marker.ns = "marker";
    marker.id = 0;
    marker.type =  visualization_msgs::Marker::CYLINDER;
    marker.action = visualization_msgs::Marker::ADD;
    marker.pose = current_position.pose; 
    marker.scale.x = 1;
    marker.scale.y = 1;
    marker.scale.z = 1;
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0; 

    ros::Rate loop_rate(0.5);

    while (ros::ok()){
        marker_pub.publish(marker);
        pub.publish(current_position);
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}