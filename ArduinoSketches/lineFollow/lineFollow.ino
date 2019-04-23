#include <motorDriver.h>

//Motor A
const int motor1Pin1  = 30;  // Pin 14 of L293
const int motor1Pin2  = 12;  // Pin 10 of L293
const int motor1Speed = 11;

//Motor B
const int motor2Pin1  = 6; // Pin  7 of L293
const int motor2Pin2  = 5;  // Pin  2 of L293
const int motor2Speed = 4;

//Create a motor driver object thing
motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);

//Line Sensor Pins Left and right
const int linePinLeft = 10;
const int linePinRight = 7;

int lineThreshold = 80;

void setup() {
  //we are going to start with FULL SPEED AHEAD, so we want to max out each of the motors
}


/*
 * WHEN WE DO THIS FOR REAL
 * PUT A TIMER INTERRUPT ON THE SENSORS
 * WE DONT NEED TO POLL THEM ALL THE TIME, JUST SOMETIMES
 * THE ROBOT IS SLOW NOT A LOT IS GOING TO CHANGE EVERY 100ms OR WHATEVER
 */
void loop() {
  // put your main code here, to run repeatedly:
  m.forward();
  
  while(readLine(linePinLeft) < lineThreshold) {
    /*
     *  Do some turning in the correct direction.
     *  we need to back up and turn right (which is heading left if you think of it like a car)
     */
     //m.slowTurn(0, 150, 255);
     m.turnLeft();
     delay(500);
  }

   while(readLine(linePinRight) < lineThreshold) {
    /*
     *  Do some turning in the correct direction.
     *  we need to back up and turn left (which makes you go right since we are backing up)
     */
     //m.slowTurn(0, 255, 150);
     m.turnRight();
     delay(500);
  }
  m.setRightMotorSpeed(255);
  m.setLeftMotorSpeed(255);
  

}
