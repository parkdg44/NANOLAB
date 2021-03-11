#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <tf/tf.h>
#include <geometry_msgs/TransformStamped.h>
#include <math.h>
#include <signal.h>
#include <termios.h>
#include <stdio.h>

#define KEYCODE_R 0x44  // 
#define KEYCODE_L 0x43  //
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71
#define KEYCODE_Stop 0x20 // Space bar

//test_mapping::Cmd_val cmd_vel;
geometry_msgs::Twist cmd_vel;
ros::Publisher cmd_pub;

void keyLoop();
void quit(int sig);

int main(int argc, char **argv)
{
  ros::init(argc, argv, "teleop");
  ros::NodeHandle nh;

  //cmd_pub = nh.advertise<test_mapping::Cmd_val>("cmd_vel", 1);
  cmd_pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  signal(SIGINT,quit);
  while (ros::ok())
  {
    keyLoop();
  }
}

int kfd = 0;
int count_ang = 0, count_lin = 0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}


void keyLoop()
{
  char c;
  bool dirty=false;

  // get the console in raw mode                                                              
  tcgetattr(kfd, &cooked);
  memcpy(&raw, &cooked, sizeof(struct termios));
  raw.c_lflag &=~ (ICANON | ECHO);
  // Setting a new line, then end of file                         
  raw.c_cc[VEOL] = 1;
  raw.c_cc[VEOF] = 2;
  tcsetattr(kfd, TCSANOW, &raw);

  puts("Reading from keyboard");
  puts("---------------------------");
  puts("Use arrow keys to move the motor.");


  for(;;)
  {
    // get the next event from the keyboard  
    // ROS_INFO("DEBUG");
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }
    // ROS_INFO("DEBUG2");
    

    //cmd_vel.yaw=0;
    //cmd_vel.linear_speed=0;
    ros::spinOnce();
    ROS_DEBUG("value: 0x%02X\n", c);

    switch(c)
    {
      case KEYCODE_U:
        ROS_DEBUG("UP");
        count_lin++;
        dirty = true;
        puts("Speed Up");
        break;
      case KEYCODE_L:
        ROS_DEBUG("LEFT");
        count_ang--;
        dirty = true;
        puts("LEFT");
        break;
      case KEYCODE_R:
        ROS_DEBUG("RIGHT");
        count_ang++;
        dirty = true;
        puts("RIGHT");
        break;
      case KEYCODE_D:
        ROS_DEBUG("DOWN");
        count_lin--;
        dirty = true;
        puts("Speed Down");
        break;
      case KEYCODE_Stop:
        ROS_DEBUG("STOP");
        count_lin=0;
        dirty = true;
        puts("Stop");
        break;
    }
   
    if(dirty ==true)
    {
      cmd_vel.linear.x = count_lin*0.25;// * 10;
      if(count_ang >=18) count_ang = 18;
      else if (count_ang <= -18) count_ang = -18;
      //cmd_vel.yaw = count_ang * 10 * M_PI / 180;
      cmd_vel.angular.z = count_ang * (M_PI / 180) ;//* 10;
      dirty=false;
      //printf("Stop lin_vel = %d \n", cmd_vel.linear.x);
      cmd_pub.publish(cmd_vel);
    }
    else
    {
      cmd_pub.publish(cmd_vel);
    }
  }
  return;
}