#include <ros.h>
#include >std_msgs/Empty.h>
#include <race/drive_values.h>
#include <Servo.h>

#define SERVO_LEFT_MAX 56
#define SERVO_RIGHT_MAX 135
#define SERVO_CENTER_VAL 97

#define THROTTLE_MIN 1540
#define THROTTLE_MAX 2000

ros::NodeHandle nh;
boolean flagStop = false;
Servo throttle;
Servo steering;

int pos = 0;
int pin = 7;
int pin2 = 6;

std_msg::Int32 str_msg;
void messageDrive(const race::drive_values& msg)
{
  if(flagStop == false)
  {
   int throttle_val = map(msg.throttle, 0, 100, THROTTLE_MIN, THROTTLE_MAX);
   int steering_val;
   if(msg.steering < 0) 
   {
     steering_val = map(msg.steering, -100, 0, SERVO_LEFT_MAX, SERVO_CENTER_VAL);
   }
   else 
   {
     steering_val = map(msg.steering, 0, 100, SERVO_CENTER_VAL, SERVO_RIGHT_MAX);
   }
  }
  else
  {
    throttle.write(1530);
    steering.write(SERVO_CENTER_VAL);
  }
}

void messageEmergencyStop( const std_msgs::Bool& flag)
{
  flagStop = flag.data; 
  if(flagStop == true)
  {
    throttle.write(1530);
    steering.write(SERVO_CENTER_VAL);
  }
}

ros::Subscriber<race::drive_values> sub_drive("drive_pwm", &messageDrive);
ros::Subscriber<std_msgs::Bool> sub_stop("eStop", &messageEmergencyStop);

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
  nh.subscribe(sub_stop);
}

void loop() {
  nh.spinOnce();
}
