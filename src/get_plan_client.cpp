#include <ros/ros.h>
#include "jialiang_han_fulltime/GetPlan.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "get_plan_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<jialiang_han_fulltime::GetPlan>("get_plan");
  jialiang_han_fulltime::GetPlan srv;
  srv.request.agent_name = argv[1];
  srv.request.goal.pose.position.x = atoi(argv[2]);
  srv.request.goal.pose.position.y = atoi(argv[3]);
  srv.request.goal.pose.position.z = atoi(argv[4]);
  ros::Publisher path_pub = n.advertise<nav_msgs::Path>("path",1);
  client.call(srv);
  // ros::service::call("get_plan",srv);
  path_pub.publish(srv.response.path);
  ros::spin();
  return 0;

}