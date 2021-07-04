// this file is the node for visulization agent
// subscribe current position on topic "agent_feedback"
// publish a cylider to rviz

#include "ros/ros.h"
#include "visualization_msgs/Marker.h"
#include "geometry_msgs/PoseStamped.h"

geometry_msgs::PoseStamped current_position;

void callback(const geometry_msgs::PoseStamped pose){
    current_position = pose;
}

int main(int argc,char **argv){

    ros::init(argc, argv, "agenet_visualization");
    ros::NodeHandle n("~");
    
    ros::Subscriber sub = n.subscribe("agent_feedback",1000,callback);

    ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker",1);   
    uint32_t shape = visualization_msgs::Marker::CYLINDER;

    ros::Rate loop_rate(1);

    while (ros::ok()){
        visualization_msgs::Marker marker;
        marker.header.frame_id = "marker";
        marker.header.stamp = ros::Time::now();
        marker.ns = "marker";
        marker.id = 0;
        marker.type = shape;
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose = current_position.pose; 
        marker.scale.x = 1;
        marker.scale.y = 1;
        marker.scale.z = 1;
        marker.color.r = 0.0f;
        marker.color.g = 1.0f;
        marker.color.b = 0.0f;
        marker.color.a = 1.0; 
        marker.lifetime = ros::Duration();
        marker_pub.publish(marker);
        loop_rate.sleep();
    }
}