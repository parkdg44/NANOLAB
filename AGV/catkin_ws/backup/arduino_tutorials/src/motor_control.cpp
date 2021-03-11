#include <ros/ros.h>
#include <signal.h>
#include <termios.h>
#include <std_msgs/UInt16.h>
#include <stdio.h>

#define KEYCODE_R 0x43 
#define KEYCODE_L 0x44
#define KEYCODE_U 0x41
#define KEYCODE_D 0x42
#define KEYCODE_Q 0x71

class MotorControl
{
public:
  MotorControl();
  void keyLoop();

private:

  ros::NodeHandle nh_;
  std_msgs::UInt16 servo;
  ros::Publisher servo_pub_;
};

MotorControl::MotorControl():
  servo()
{
  servo_pub_ = nh_.advertise<std_msgs::UInt16>("servo", 1);
}

int kfd = 0;
struct termios cooked, raw;

void quit(int sig)
{
  (void)sig;
  tcsetattr(kfd, TCSANOW, &cooked);
  ros::shutdown();
  exit(0);
}

int count=0;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "motor_control");
  MotorControl motor_control;

  signal(SIGINT,quit);

  motor_control.keyLoop();
  
  return(0);
}


void MotorControl::keyLoop()
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
    if(read(kfd, &c, 1) < 0)
    {
      perror("read():");
      exit(-1);
    }

    servo.data=0;
    ROS_DEBUG("value: 0x%02X\n", c);
  
    switch(c)
    {
      case KEYCODE_U:
        ROS_DEBUG("UP");
        count++;
        if(count>=18)count=18;
        dirty = true;
        break;
      case KEYCODE_D:
        ROS_DEBUG("DOWN");
        count--;
        if(count<=0)count=0;
        dirty = true;
        break;
    }
   
    if(dirty ==true)
    {
      servo.data=count*10;
      servo_pub_.publish(servo);    
      dirty=false;
    }
  }
  return;
}