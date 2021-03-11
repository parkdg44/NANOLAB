//convert point cloud image to ros message
#include <ros/ros.h>
#include "sensor_msgs/PointCloud2.h"
#include <sensor_msgs/point_cloud2_iterator.h>
#include "geometry_msgs/Point.h"
#include <math.h>

sensor_msgs::PointCloud2 pcl2;
int width = 640, height = 480;
// realsense camera 
// width = 640, height = 480

geometry_msgs::Point box_location;

void pixelTo3DPoint(const sensor_msgs::PointCloud2 pCloud, const int u, const int v, geometry_msgs::Point &p)
    {
      // get width and height of 2D point cloud data

      // Convert from u (column / width), v (row/height) to position in array
      // if(u>640 ||v>480) ROS_INFO("DO NOT OVER width or height");
      
      // where X,Y,Z data starts
      int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;

      // compute position in array where x,y,z data start
      int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
      int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
      int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

      float X = 0.0;
      float Y = 0.0;
      float Z = 0.0;

      memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
      memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
      memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));

     // put data into the point p
      p.x = X;
      p.y = Y;
      p.z = Z;

    }
void cloud_callback (const sensor_msgs::PointCloud2ConstPtr& cloud_msg){
    
    pcl2.data = cloud_msg->data;
    pcl2.fields = cloud_msg->fields;
    pcl2.height = cloud_msg->height;
    pcl2.width = cloud_msg->width;
    pcl2.point_step = cloud_msg->point_step;
    pcl2.row_step = cloud_msg->row_step;
    
    pixelTo3DPoint(pcl2,(pcl2.width/2),(pcl2.height/2),box_location);

    ROS_INFO("x: %f.2 y: %f.2",box_location.x,box_location.y);
//    ROS_INFO("height: %d width: %d",pcl2.point_step,pcl2.row_step);
}

int main (int argc, char** argv) {
     ros::init (argc, argv, "find_box");
     ros::NodeHandle nh;
     ros::Rate loop_rate(10);
     ros::Subscriber sub = nh.subscribe("/camera/depth/color/points", 1, cloud_callback);
     ros::spin();
 }
