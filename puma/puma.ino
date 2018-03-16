#include <SoftwareSerial.h> 
#include <Servo.h>

#define SERVO_LEFT_MAX 56
#define SERVO_CENTER_VAL 97
#define SERVO_RIGHT_MAX 135

#define THROTTLE_MIN 1540
#define THROTTLE_MAX 2000

#define SERVO_LEFT_MAX 56
#define SERVO_CENTER_VAL 97

SoftwareSerial BTSerial(2, 3); 
Servo throttle;
Servo steering;
int pos = 0;
int pin = 7;
int pin2 = 6;

void setup() {
  BTSerial.begin(9600);
  throttle.attach(pin);
  steering.attach(pin2);
  // arming
  for (pos = 90; pos <= 100; pos += 1) { 
    throttle.write(pos);             
    delay(150);                       
  }
}

void loop() {
  if(BTSerial.available()) {
    char bt;  
    bt = BTSerial.read();
    if(bt == 'l') {
      steering.write(SERVO_RIGHT_MAX);
      throttle.write(THROTTLE_MIN);
    }
    else if(bt == 'r') {
      steering.write(SERVO_LEFT_MAX);
      throttle.write(THROTTLE_MIN);
    }
    else if(bt == 'f'){
      steering.write(SERVO_CENTER_VAL);
      throttle.write(THROTTLE_MIN);
    }
    else if(bt == 's'){
      throttle.write(1530);
    }
  }
}
