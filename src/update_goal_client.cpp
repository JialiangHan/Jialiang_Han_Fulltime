#include <ros/ros.h>
#include "jialiang_han_fulltime/UpdateGoal.h"

int main(int argc, char** argv)
{
  ros::init(argc, argv, "update_goal_client");

  ros::NodeHandle n;
  ros::NodeHandle nh("~");
  ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::UpdateGoal>("update_goal");
  jialiang_han_fulltime::UpdateGoal srv;
  srv.request.agent_name = argv[1];
  srv.request.goal.pose.position.x = atoi(argv[2]);
  srv.request.goal.pose.position.y = atoi(argv[3]);
  srv.request.goal.pose.position.z = atoi(argv[4]);
  ros::Publisher path_pub = nh.advertise<nav_msgs::Path>("path", 1);
  // call service not work
  client.call(srv);
  ros::Rate loop_rate(1);
  nav_msgs::Path path;
  path = srv.response.path;
  while (ros::ok())
  {
    path_pub.publish(path);
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}