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

#define SLIP_MODULOUS 1.0f

ros::Time current_time, last_time;

class dead_node
{
public:
  dead_node();
  double lin_vel, ang_vel, theta, dt;
  double yaw_vel = 0; 
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
  geometry_msgs::TransformStamped odom_trans;
  sensor_msgs::Imu imu_data;
  void valueCallback(const geometry_msgs::TwistConstPtr &dead_val);
  //void yawCallback(const test_mapping::Cmd_valConstPtr &yaw_val);
  void yawCallback(const geometry_msgs::TwistConstPtr &yaw_val);

};

dead_node::dead_node()
{
  value_sub_ = nh_.subscribe<geometry_msgs::Twist>("dead_value", 1, &dead_node::valueCallback, this);
  //yaw_sub_ = nh_.subscribe<test_mapping::Cmd_val>("yaw_val", 1, &dead_node::yawCallback, this);
  yaw_sub_ = nh_.subscribe<geometry_msgs::Twist>("yaw_val", 1, &dead_node::yawCallback, this);
  odom_pub_ = nh_.advertise<nav_msgs::Odometry>("odom", 1);
  imu_pub_ = nh_.advertise<sensor_msgs::Imu>("imu_data", 1);
  timer1 = nh_.createTimer(ros::Duration(0.01), &dead_node::timerCallback, this);
  timer1.start();
}

void dead_node::valueCallback(const geometry_msgs::TwistConstPtr &dead_val)
{
  current_time = ros::Time::now();
  dt = (current_time - last_time).toSec();
  last_time = current_time;
  
  //dt = t / 100.0;
  //t = 0;
  lin_vel = dead_val->linear.x;
  if(lin_vel >= 10000) lin_vel = 0;
  ang_vel = dead_val->angular.z;
  if(ang_vel >= M_PI) ang_vel = 0;
   // dead_reckoning Yaw

  if(yaw != yaw_past & dt !=0) yaw_vel = (yaw - yaw_past)/dt;//
  else yaw_vel=0.0;

  double delta_x = (lin_vel * dt * cos(yaw + (yaw-yaw_past)/2) * SLIP_MODULOUS);
  double delta_y = (lin_vel * dt * sin(yaw + (yaw-yaw_past)/2) * SLIP_MODULOUS);
  

  //double delta_x = (lin_vel * dt * cos(yaw) * SLIP_MODULOUS);
  //double delta_y = (lin_vel * dt * sin(yaw) * SLIP_MODULOUS);

  x += delta_x;
  y += delta_y;
  
  geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(yaw);
  
  odom_trans.header.stamp = ros::Time::now();
  odom_trans.header.frame_id = "odom";
  odom_trans.child_frame_id = "base_link";

  odom_trans.transform.translation.x = x;
  odom_trans.transform.translation.y = y;
  odom_trans.transform.translation.z = 0.0;
  odom_trans.transform.rotation = odom_quat;

  tfbroadcaster.sendTransform(odom_trans);

  nav_msgs::Odometry odom;
  odom.header.stamp = ros::Time::now();
  odom.header.frame_id = "odom";
  //set the position
  odom.pose.pose.position.x = x;
  odom.pose.pose.position.y = y;
  odom.pose.pose.position.z = 0.0;
  odom.pose.pose.orientation = odom_quat;
  //set the velocity
  odom.child_frame_id = "base_link";
  odom.twist.twist.linear.x = lin_vel * cos(yaw + (yaw-yaw_past)/2);
  odom.twist.twist.linear.y = lin_vel * sin(yaw + (yaw-yaw_past)/2);
  odom.twist.twist.angular.z = yaw_vel; //ang_vel;

  yaw_past = yaw;
  odom_pub_.publish(odom);
}
/* 
void dead_node::yawCallback(const test_mapping::Cmd_valConstPtr &yaw_val)
{
  yaw = (yaw_val->yaw);
}
*/

void dead_node::yawCallback(const geometry_msgs::TwistConstPtr &yaw_val)
{
  yaw = (yaw_val->angular.z );
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
    ROS_INFO("yaw %0.5f yaw_past %0.5f yaw_vel %0.10f dt %0.10f ", dead_node.yaw, dead_node.yaw_past ,dead_node.yaw_vel, dead_node.dt);
    ros::spinOnce();
  }
}

