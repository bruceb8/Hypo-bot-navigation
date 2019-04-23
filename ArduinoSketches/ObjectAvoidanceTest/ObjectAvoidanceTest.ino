#include <motorDriver.h>
#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(18, 19);
Encoder knobRight(2, 3);
//Motor A
const int motor1Pin1  = 13;  // Pin 14 of L293
const int motor1Pin2  = 12;  // Pin 10 of L293
const int motor1Speed = 11;

//Motor B
const int motor2Pin1  = 6; // Pin  7 of L293
const int motor2Pin2  = 5;  // Pin  2 of L293
const int motor2Speed = 4;

const int MESpeedLeft = 255;
const int MESpeedRight = 255;

//Create a motor driver object thing
motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);


int lDPin = A0;
int rDPin = A1;

void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
      //we are going to start with FULL SPEED AHEAD, so we want to max out each of the motors
  m.setRightMotorSpeed(255);
  m.setLeftMotorSpeed(255);

}

void loop() {
  // put your main code here, to run repeatedly:
  m.forward();
  if(readDistance(lDPin) < 20) {
    //Do something
  }
  
}
