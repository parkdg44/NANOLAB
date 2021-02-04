#include <ros/ros.h>
#include "sensor_msgs/Imu.h"
#include <geometry_msgs/Twist.h>
#include <test_mapping/Cmd_val.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <math.h>

#define SLIP_MODULOUS 1.10f

class dead_node
{
public:
  dead_node();
  double lin_vel, ang_vel, theta;
  double x, y;
  double yaw, yaw_past, yaw_cal;

private:
  void timerCallback(const ros::TimerEvent &event);
  int t;
  double x_past = 0, y_past = 0, theta_past = 0;
  double yaw_forcal=0;
  double cal_value;
  double yaw_first;
  int cal_count=0;
  bool isCal = false; 
  bool isCal_first = false;
  ros::NodeHandle nh_;
  ros::Subscriber value_sub_;
  ros::Subscriber yaw_sub_;
  ros::Publisher odom_pub_;
  ros::Publisher imu_pub_;
  ros::Timer timer1;
  tf::TransformBroadcaster tfbroadcaster;
  geometry_msgs::TransformStamped tfs_msg;
  sensor_msgs::Imu imu_data;
  void valueCallback(const geometry_msgs::TwistConstPtr &dead_val);
  void yawCallback(const test_mapping::Cmd_valConstPtr &yaw_val);
};

dead_node::dead_node()
{
  value_sub_ = nh_.subscribe<geometry_msgs::Twist>("dead_value", 1, &dead_node::valueCallback, this);
  yaw_sub_ = nh_.subscribe<test_mapping::Cmd_val>("yaw_val", 1, &dead_node::yawCallback, this);
  odom_pub_ = nh_.advertise<nav_msgs::Odometry>("odom", 1);
  imu_pub_ = nh_.advertise<sensor_msgs::Imu>("imu_data", 1);
  timer1 = nh_.createTimer(ros::Duration(0.01), &dead_node::timerCallback, this);
  timer1.start();
}

void dead_node::valueCallback(const geometry_msgs::TwistConstPtr &dead_val)
{
  double dt = t / 100.0;
  t = 0;
  lin_vel = dead_val->linear.x;
  ang_vel = dead_val->angular.z;

  x = x_past + (lin_vel * dt * cos(yaw) * SLIP_MODULOUS);
  y = y_past + (lin_vel * dt * sin(yaw) * SLIP_MODULOUS);

  x_past = x;
  y_past = y;

  tfs_msg.header.stamp = ros::Time::now();
  tfs_msg.header.frame_id = "odom";
  tfs_msg.child_frame_id = "base_link";

  tf::Quaternion q = tf::Quaternion(0, 0, yaw);

  tfs_msg.transform.rotation.x = q.getX();
  tfs_msg.transform.rotation.y = q.getY();
  tfs_msg.transform.rotation.z = q.getZ();
  tfs_msg.transform.rotation.w = q.getW();

  tfs_msg.transform.translation.x = x;
  tfs_msg.transform.translation.y = y;
  tfs_msg.transform.translation.z = 0;

  tfbroadcaster.sendTransform(tfs_msg);

  nav_msgs::Odometry odom;
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "odom";

  //set the position
  odom.pose.pose.position.x = x;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation.x = q.getX();
  odom.pose.pose.orientation.y = q.getY();
  odom.pose.pose.orientation.z = q.getZ();
  odom.pose.pose.orientation.w = q.getW();

  //set the velocity
  odom.child_frame_id = "base_link";
  odom.twist.twist.linear.x = lin_vel * cos(yaw);
  odom.twist.twist.linear.y = lin_vel * sin(yaw);
  odom.twist.twist.angular.z = ang_vel;

  odom_pub_.publish(odom);
}

void dead_node::yawCallback(const test_mapping::Cmd_valConstPtr &yaw_val)
{
  yaw = (yaw_val->yaw);
}

void dead_node::timerCallback(const ros::TimerEvent &event)
{
  t++;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "raw_data_to_tf");
  ros::NodeHandle nh;

  dead_node dead_node;

  while (ros::ok())
  {
    ros::spinOnce();
  }
}

