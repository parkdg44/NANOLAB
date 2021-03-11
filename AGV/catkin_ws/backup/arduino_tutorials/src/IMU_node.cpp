#include <ros/ros.h>
#include "sensor_msgs/Imu.h"

class IMU_node
{
  public:
  IMU_node();

  private:
  ros::NodeHandle nh_;
  sensor_msgs::Imu Imu_value;  
  ros::Subscriber value_sub_;
  void valueCallback(const sensor_msgs::ImuConstPtr &Imu);
};

IMU_node::IMU_node():
  Imu_value()
{
  value_sub_ = nh_.subscribe<sensor_msgs::Imu>("Imu_value",1, &IMU_node::valueCallback, this);
}

void IMU_node::valueCallback(const sensor_msgs::ImuConstPtr &Imu)
{
  Imu_value.orientation.x = Imu->orientation.x;
  Imu_value.orientation.y = Imu->orientation.y;
  Imu_value.orientation.z = Imu->orientation.z;

  Imu_value.linear_acceleration.x = Imu->linear_acceleration.x;
  Imu_value.linear_acceleration.y = Imu->linear_acceleration.y;
  Imu_value.linear_acceleration.z = Imu->linear_acceleration.z;

  Imu_value.angular_velocity.x = Imu->angular_velocity.x;
  Imu_value.angular_velocity.y = Imu->angular_velocity.y;
  Imu_value.angular_velocity.z = Imu->angular_velocity.z;
}

int main(int argc, char** argv)
{
  ros::init(argc, argv, "IMU_node");
  IMU_node Imu_node;
  ros::spin();
}