#include <ros.h>
#include <race/drive_values.h>
#include <std_msgs/Bool.h>
#include <std_msgs/Empty.h>
#include <Servo.h>

#define SERVO_LEFT_MAX 56
#define SERVO_RIGHT_MAX 135
#define SERVO_CENTER_VAL 97

#define THROTTLE_STOP 1500
#define FORWARD_MIN 1540
#define REVERSE_MIN 1450

ros::NodeHandle nh;
boolean flagEStop = true;
Servo throttle;
Servo steering;

int pos = 0;
int pin = 7;
int pin2 = 6;

void messageDrive(const race::drive_values &msg) {
  if (flagEStop == false) {
    // int throttle_val = map(msg.throttle, 0, 100, THROTTLE_MIN, THROTTLE_MAX);
    int steering_val;
    steering_val = map(msg.steering, 0, 200, SERVO_LEFT_MAX, SERVO_RIGHT_MAX);
    steering.write(steering_val);
    if(msg.throttle == 1) {
      throttle.write(FORWARD_MIN);
    }
    else if (msg.throttle == -1) {
      throttle.write(REVERSE_MIN);
    }
    else {
      throttle.write(THROTTLE_STOP);
    }
  } else {
    throttle.write(THROTTLE_STOP);
    steering.write(SERVO_CENTER_VAL);
  }
}
void messageThrottle(const std_msgs::Bool &msg) { 
  flagEStop = msg.data; 
}

ros::Subscriber<race::drive_values> sub_drive("Control", &messageDrive);
ros::Subscriber<std_msgs::Bool> sub_eStop("e_Stop", &messageThrottle);

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
  nh.subscribe(sub_eStop);
}

void loop() { nh.spinOnce(); }
