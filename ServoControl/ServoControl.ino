/*
 * rosserial Servo Control Example
 *
 * This sketch demonstrates the control of hobby R/C servos
 * using ROS and the arduiono
 * 
 * For the full tutorial write up, visit
 * www.ros.org/wiki/rosserial  _arduino_demos
 *
 * For more information on the Arduino Servo Library
 * Checkout :
 * http://www.arduino.cc/en/Reference/Servo
 */

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <Servo.h> 
#include <ros.h>
#include <std_msgs/UInt16.h>
#define SERVO_LEFT_MAX 56
#define SERVO_RIGHT_MAX 135
#define SERVO_CENTER_VAL 97

ros::NodeHandle  nh;

Servo servo;

void servo_cb( const std_msgs::UInt16& cmd_msg){
  //servo.write(map(cmd_msg.data, 0, 180, SERVO_LEFT_MAX, SERVO_RIGHT_MAX));
  servo.write((int)cmd_msg.data);
}


ros::Subscriber<std_msgs::UInt16> sub("servo", servo_cb);

void setup(){
  nh.initNode();
  nh.subscribe(sub);

  servo.attach(6); //attach it to pin 9
  servo.write(SERVO_CENTER_VAL);
}

void loop(){
  nh.spinOnce();
  delay(1);
}

