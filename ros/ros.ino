#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <Servo.h>

#define SERVO_LEFT_MAX 56
#define SERVO_RIGHT_MAX 135
#define SERVO_CENTER_VAL 97

#define THROTTLE_MIN 1540
#define THROTTLE_MAX 2000

ros::NodeHandle nh;
boolean flagStart = true;
Servo throttle;
Servo steering;

int pos = 0;
int pin = 7;
int pin2 = 6;

void messageDrive(const std_msgs::UInt16& msg)
{  
  if(flagStart == true)
  {
   //int throttle_val = map(msg.throttle, 0, 100, THROTTLE_MIN, THROTTLE_MAX);
   throttle.write(1540);
   int steering_val;
   steering_val = map(msg.data, 0, 200, SERVO_LEFT_MAX, SERVO_RIGHT_MAX);
   steering.write(steering_val);
  }
  else
  {
    throttle.write(1500);
    steering.write(SERVO_CENTER_VAL);
  }
}
void messageThrottle(const std_msgs::Bool& msg)
{
  flagStart = msg.data;
}
ros::Subscriber<std_msgs::UInt16> sub_drive("Controller", &messageDrive);
ros::Subscriber<std_msgs::Bool> sub_throttle("throttle", &messageThrottle);
void setup() {
  throttle.attach(pin);
  steering.attach(pin2);
  // arming
  for (pos = 90; pos <= 180; pos += 1) {
    throttle.write(pos);
    delay(150);
  }
  nh.initNode();
  nh.subscribe(sub_drive);
  nh.subscribe(sub_throttle);
}

void loop() {
  nh.spinOnce();
}
