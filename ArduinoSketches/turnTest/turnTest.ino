/*
 * The purpose of this sketch is to get some test measuremanets for turning
 * We should turn at a low speed to keep precision to avoid the slippin gof the robot's tires
 * This is for precision turning, being off by a degree 
 */

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

//Create a motor driver object thing
motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);


void setup() {
  // put your setup code here, to run once:
  m.setRightMotorSpeed(230);
  m.setLeftMotorSpeed(230);
  Serial.begin(57600);

}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  rightTurnDegrees(90);
  //THIS IS 2700 TICKS
  delay(10000);
  
}
