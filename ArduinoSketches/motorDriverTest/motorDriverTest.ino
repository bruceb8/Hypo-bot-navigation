#include <motorDriver.h>

//Motor A
const int motor1Pin1  = 13;  // Pin 14 of L293
const int motor1Pin2  = 12;  // Pin 10 of L293
const int motor1Speed = 11;

//Motor B
const int motor2Pin1  = 6; // Pin  7 of L293
const int motor2Pin2  = 5;  // Pin  2 of L293
const int motor2Speed = 4;


motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);

void setup() {
  // put your setup code here, to run once:
  m.setRightMotorSpeed(255);
  m.setLeftMotorSpeed(255);
}

void loop() {
  //Move the car forward
 /* m.slowTurn(1, 150, 255);
  delay(2000);
  m.slowTurn(1, 255, 150);
  delay(2000);
    m.setRightMotorSpeed(255);
  m.setLeftMotorSpeed(255);*/
  m.turnLeft();
  delay(2000);

/*
  m.forward();
  delay(2000);
  
  m.reverse();
  delay(2000);

  m.turnRight();
  delay(2000);

  m.turnLeft();
  delay(2000);
  */
  // put your main code here, to run repeatedly:

}
