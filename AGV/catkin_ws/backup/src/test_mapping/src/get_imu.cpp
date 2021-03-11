// I got this code from : http://www.easysw.com/~mike/serial/serial.html
// Also: http://www.cplusplus.com/doc/tutorial/files/

#include <ros/ros.h>
#include "sensor_msgs/Imu.h"
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include "test_mapping/Cmd_val.h"
#include <serial/serial.h>
#include <math.h>

#include <stdio.h>   //Standard input/readL definitions
#include <string.h>  //String function definitions
#include <unistd.h>  //UNIX standard function definitions
#include <fcntl.h>   //File control definitions
#include <errno.h>   //Error number definitions
#include <termios.h> //POSIX terminal control definitions
#include <iostream>  //Input-Output Streams

double P[2][2] = {0.0f};
double Q_angle   = 0.003f;
double Q_bias    = 0.003f;
double R_measure = 0.03f;
double angle_kalman = 0.0f; // Reset the angle_kalman
double bias  = 0.0f; // Reset bias
double rate = 0.0f;

double K[2] = {0.0f}; // Kalman gain - This is a 2x1 vector
double y=0.0f; // Angle difference
double S=0.0f; // Estimate error
double getAngle(double newAngle, double newRate, double dt);

std::string port = "";
double quat[4];
std::string RPY[4];
double ax,ay,az;
double roll = 0, pitch = 0, yaw = 0,yaw_past =0;
double yaw_first=0;
double yaw_forcal = 0, yaw_cal = 0, yaw_first_cal = 0;
double cal_value=0;
double error = 0;
int cal_count = 0;

bool isCal = false; bool isCal_first = false;
int j = 0;
int iscal = 0;
int open_port();
static void toEulerAngle(const tf::Quaternion q, double& roll, double& pitch, double& yaw);
test_mapping::Cmd_val yaw_val,yaw_kal;
ros::Publisher yaw_pub,yaw_kal_pub;

double d_theta, theta=0;

class IMU_pub
{
  public:
  void pub_quat(tf::Quaternion q);
  IMU_pub();
  int t_dead,t_imu;
  double angle_dead,ang_vel;

  private:
  void timerCallback_imu(const ros::TimerEvent &event);
  void timerCallback_dead(const ros::TimerEvent &event);
  void valueCallback(const geometry_msgs::TwistConstPtr &dead_val);
  ros::Subscriber sub_dead;
  ros::Timer timer1;
  ros::Timer timer2;
  ros::NodeHandle nh_;
  geometry_msgs::TransformStamped tfs_msg;
  tf::TransformBroadcaster tfbroadcaster;
  tf::Quaternion q;
};

int main(int argc, char **argv)
{
	ros::init(argc, argv, "get_imu");
	ros::NodeHandle nh_private("~");
	ros::NodeHandle nh;
	IMU_pub IMU_pub;

	nh_private.param<std::string>("IMU_PORT", port, "/dev/ttyUSB0");
	
	yaw_pub = nh.advertise<test_mapping::Cmd_val>("yaw_val", 1);
	yaw_kal_pub = nh.advertise<test_mapping::Cmd_val>("yaw_kal", 1);
	

	nh_private.getParam("IMU_PORT", port);

	int sPort = -1;
	int isread = 0;

	sPort = open_port();

	while (ros::ok())
	{
		char readL[60] = "";
		if (sPort != -1)
		{

			isread = read(sPort, readL, 60);
			
			//sPort.write('a', 1);  // A class method can be used to send as well. This write is cleaner and more C++

			if (isread < 0 || readL[0] != '*')
			{
				// ROS_INFO("Failed to write to port");
			}
			else
			{
				int size = 1;
				for (int i=0; ; i++) 
				{
					if(readL[i]==0) 
					{
						size=i-1;
						//ROS_INFO("%d",readL[i-1]);				
						break;
					}
				}
				
				std::string buff(readL,size);
				//0~size-1까지
				buff.erase(0,1);
				
				int pos[6]={0}, a = 0;
				std::string accel[3];
				
				
				for (int i = 0;; i++)
				{
					if (a >= 6)
						break;
						
					if (buff[i] == ',' && pos[a] == 0)
					{
						pos[a] = i;
						a++;
					}

				}
				/*
				RPY[0] = buff.substr(0, pos[0]);
				RPY[1] = buff.substr(pos[0] + 1, (pos[1] - pos[0] - 1));
				RPY[2] = buff.substr(pos[1] + 1, (pos[2] - pos[1] - 1));
				RPY[3] = buff.substr(pos[2] + 1, (pos[3] - pos[2] - 1));
				accel[0] = buff.substr(pos[3] + 1, (pos[4] - pos[3] - 1));
				accel[1] = buff.substr(pos[4] + 1, (pos[5] - pos[4] - 1));
				accel[2] = buff.substr(pos[5] + 1, size - 1);
				tf::Quaternion q = tf::Quaternion(quat[0],quat[1],quat[2],quat[3]);

				//IMU_pub.pub_quat(q);
				tf::Matrix3x3 m(q);
				m.getRPY(yaw, pitch, roll);
				yaw = yaw/2;

				tf::Quaternion q_yaw = tf::Quaternion(yaw,0.0,0.0);
				yaw_val.yaw = yaw;
				*/
				// string -> 쿼터니언 변환 
				RPY[0] = buff.substr(0, pos[0]);
				RPY[1] = buff.substr(pos[0] + 1, (pos[1] - pos[0] - 1));
				RPY[2] = buff.substr(pos[1] + 1, (pos[2] - pos[1] - 1));
				accel[0] = buff.substr(pos[2] + 1, (pos[3] - pos[2] - 1));
				accel[1] = buff.substr(pos[3] + 1, (pos[4] - pos[3] - 1));
				accel[2] = buff.substr(pos[4] + 1, size - 1);

				roll = atof(RPY[0].c_str());
				pitch = atof(RPY[1].c_str());
				yaw = atof(RPY[2].c_str());
				ax = atof(accel[0].c_str());
				ay = atof(accel[1].c_str());
				az = atof(accel[2].c_str());

				roll = roll / 180 * M_PI;
				pitch = pitch / 180 * M_PI;
				yaw = yaw / 180 * M_PI;

				if (yaw_first == 0)
					yaw_first = yaw;
				yaw = yaw - yaw_first;

				if (yaw >= M_PI)
					yaw = yaw - 2 * M_PI;
				if (yaw <= -M_PI)
					yaw = yaw + 2 * M_PI;

				//double tau = 1.018;
				double tau = 1.000;
				double dt = IMU_pub.t_imu / 100.0;
				IMU_pub.t_imu = 0;

				d_theta = (tau / (tau + dt)) * d_theta + (tau / (tau + dt)) * (yaw - yaw_past);
				if (fabs(d_theta) <= 0.00020) d_theta = 0;
				yaw_past = yaw;

				if (isCal == false)
				{
					if (isCal_first == false)
					{
						yaw_first_cal = yaw;
						isCal_first = true;
					}
					double A = (yaw) - (yaw_first_cal);
					if (fabs(A) <= 0.0300)
					{
						yaw_forcal += A;
						cal_count++;
					}

					ROS_INFO("cal_count : %3d", cal_count);

					if ((cal_count >= 100) && (isCal_first == true))
					{
						cal_value = yaw_forcal / cal_count;
						isCal = true;
						cal_value = cal_value * 0.01;
						if(fabs(cal_value)>0.0002)
						{
							isCal = false;
							isCal_first = false;
							cal_count = 0;
							yaw_forcal = 0;
							yaw_first_cal=0;
						}
						ROS_INFO("cal_value :  %.4f, yaw_first = %.4f yaw_ave = %.4f", cal_value, yaw_first_cal, yaw_forcal / cal_count);
					}
					
				}
				else
				{
					//d_theta =  0.85 * d_theta + 0.85 * (yaw-yaw_past);
					theta += d_theta * dt;
					if (theta >= M_PI)
						theta = theta - 2 * M_PI;
					if (theta <= -M_PI)
						theta = theta + 2 * M_PI;

					ROS_INFO("HPF :  %.4f Yaw : %.4f, alpha = %.4f", -theta*180/M_PI, -yaw*180/M_PI, tau / (tau + dt));
					//yaw_past = yaw;
					//////////////////	
					//error += cal_value;
					//////////////////
					//////////////
					//yaw_cal = yaw - error;
					//////////////
					//ROS_INFO("yaw = %.4f", yaw*180.0f/M_PI);


					// 칼만 필터 식 적용
					//ROS_INFO("KALMAN :  %.4f Yaw : %.4f", -angle_kalman, -yaw*180/M_PI);

					//yaw_val.yaw = -yaw;
					//yaw_kal.yaw = -theta;
					yaw_val.yaw = -theta;
					yaw_kal.yaw = -yaw;
				}
				yaw_pub.publish(yaw_val);
				yaw_kal_pub.publish(yaw_kal);
			}
		};
		ros::spinOnce();
	}
}

//open_port() - Opens serial port and returns file descriptor on success or -1 on error
int open_port(void)
{
	int fd; //File descriptor for the port
	struct termios options;
	const char *s = port.c_str();
	ROS_INFO("Try Connect %s", s);
	fd = open(s, O_RDWR | O_NOCTTY | O_NDELAY);

	if (fd == -1)
	{
		//Could not open the port.
		std::cout << "Port Failed to Open\n";
	}
	else
	{
		fcntl(fd, F_SETFL, FNDELAY); // Sets the read() function to return NOW and not wait for data to enter buffer if there isn't_imu anything there.

		//Configure port for 8N1 transmission
		tcgetattr(fd, &options);			 //Gets the current options for the port
		cfsetispeed(&options, B115200);		 //Sets the Input Baud Rate
		cfsetospeed(&options, B115200);		 //Sets the Output Baud Rate
		options.c_cflag |= (CLOCAL | CREAD); //? all these set options for 8N1 serial operations
		options.c_cflag &= ~PARENB;			 //?
		options.c_cflag &= ~CSTOPB;			 //?
		options.c_cflag &= ~CSIZE;			 //?
		options.c_cflag |= CS8;				 //?

		tcsetattr(fd, TCSANOW, &options); //Set the new options for the port "NOW"

		ROS_INFO("seems like everything is ok, keep going!");
	};

	return (fd);
};

IMU_pub::IMU_pub()
{
	timer1 = nh_.createTimer(ros::Duration(0.0001), &IMU_pub::timerCallback_imu, this);
	timer1.start();
	timer2 = nh_.createTimer(ros::Duration(0.0001), &IMU_pub::timerCallback_dead, this);
	timer2.start();
	sub_dead = nh_.subscribe<geometry_msgs::Twist>("dead_value", 1, &IMU_pub::valueCallback, this);
}


void IMU_pub::timerCallback_imu(const ros::TimerEvent &event)
{
  t_imu++; 
}

void IMU_pub::timerCallback_dead(const ros::TimerEvent &event)
{
  t_dead++; 
}

void IMU_pub::pub_quat(tf::Quaternion q)
{
  tfs_msg.header.stamp    = ros::Time::now();
  tfs_msg.header.frame_id = "base_link";
  tfs_msg.child_frame_id  = "imu_value";
  
  tfs_msg.transform.rotation.x = q[0];
  tfs_msg.transform.rotation.y = q[1];
  tfs_msg.transform.rotation.z = q[2];
  tfs_msg.transform.rotation.w = q[3];

  tfs_msg.transform.translation.x = 0.0;
  tfs_msg.transform.translation.y = 0.0;
  tfs_msg.transform.translation.z = 0.0;

  tfbroadcaster.sendTransform(tfs_msg);
}

void IMU_pub::valueCallback(const geometry_msgs::TwistConstPtr &dead_val)
{
  double dt = t_dead / 100.0;
  t_dead = 0;
  ang_vel = dead_val->angular.z;
  angle_dead += ang_vel*dt;

  double newRate = ang_vel;
  double newAngle = yaw * (180 / M_PI);

  if (!(std::isinf(newRate)) && !(std::isnan(newRate)))
  {
	  angle_kalman = getAngle(newAngle, newRate, dt);
  }
  //yaw_kal.yaw = -angle_kalman/180*M_PI;

}

static void toEulerAngle(const tf::Quaternion q, double& roll, double& pitch, double& yaw)
{
	// roll (x-axis rotation)
	double sinr_cosp = +2.0 * (q.w() * q.x() + q.y() * q.z());
	double cosr_cosp = +1.0 - 2.0 * (q.x() * q.x() + q.y() * q.y());
	roll = atan2(sinr_cosp, cosr_cosp);

	// pitch (y-axis rotation)
	double sinp = +2.0 * (q.w() * q.y() - q.z() * q.x());
	if (fabs(sinp) >= 1)
		pitch = copysign(M_PI / 2, sinp); // use 90 degrees if out of range
	else
		pitch = asin(sinp);

	// yaw (z-axis rotation)
	double siny_cosp = +2.0 * (q.w() * q.z() + q.x() * q.y());
	double cosy_cosp = +1.0 - 2.0 * (q.y() * q.y() + q.z() * q.z());  
	yaw = atan2(siny_cosp, cosy_cosp);
}

double getAngle(double newAngle, double newRate, double dt)
{
  // KasBot V2  -  Kalman filter module - http://www.x-firm.com/?page_id=145
  // Modified by Kristian Lauszus
  // See my blog post for more information: http://blog.tkjelectronics.dk/2012/09/a-practical-approach-to-kalman-filter-and-how-to-implement-it

  // Discrete Kalman filter time update equations - Time Update ("Predict")
  
  // Update xhat - Project the state ahead
  /* Step 1 */
  rate = newRate - bias;
  angle_kalman += dt * rate;

  // Update estimation error covariance - Project the error covariance ahead
  /* Step 2 */
  P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  // Discrete Kalman filter measurement update equations - Measurement Update ("Correct")
  // Calculate Kalman gain - Compute the Kalman gain
  /* Step 4 */
  S = P[0][0] + R_measure;
  /* Step 5 */
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;

  // Calculate angle_kalman and bias - Update estimate with measurement zk (newAngle)
  /* Step 3 */
  y = newAngle - angle_kalman;
  /* Step 6 */
  angle_kalman += K[0] * y;
  bias += K[1] * y;

  // Calculate estimation error covariance - Update the error covariance
  
  /* Step 7 */
  P[0][0] -= K[0] * P[0][0];
  P[0][1] -= K[0] * P[0][1];
  P[1][0] -= K[1] * P[0][0];
  P[1][1] -= K[1] * P[0][1];

  return angle_kalman;

};