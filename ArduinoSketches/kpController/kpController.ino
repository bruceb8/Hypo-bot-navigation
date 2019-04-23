/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */
#include <motorDriver.h>
#include <Encoder.h>

// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(20, 21);
Encoder knobRight(3, 2);
//   avoid using pins with LEDs attached

//Motor A
const int motor1Pin1  = 30;  // Pin 14 of L293
const int motor1Pin2  = 12;  // Pin 10 of L293
const int motor1Speed = 11;

//Motor B
const int motor2Pin1  = 6; // Pin  7 of L293
const int motor2Pin2  = 5;  // Pin  2 of L293
const int motor2Speed = 4;

motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);


//Left motor seems faster so it will be the slave
long lSpeed = 235;

//Right motor is the master "MATCH ME" SCREAMS THE RIGHT SIDE
long rSpeed = 230;

//NOW WE DO THE MAGIC K... MAGIK

double kp = 5;  //FLASHBACKS OF GUTMANN  We are gonna divide by this dont you worry your little head

void setup() {
  Serial.begin(57600);
  Serial.println("TwoKnobs Encoder Test:");
  m.setRightMotorSpeed(rSpeed);
  m.setLeftMotorSpeed(lSpeed);
}

double positionLeft  = -999;
double positionRight = -999;

void loop() {
//  m.forward();
//  long newLeft, newRight;
//  newLeft = knobLeft.read();
//  newRight = knobRight.read();
//  if (newLeft != positionLeft || newRight != positionRight) {
//    positionLeft = abs(newLeft);
//    positionRight = abs(newRight);
//    long error = positionRight - positionLeft;
//    //If master is faster than slave
//    if( error > 0){
//      lSpeed = lSpeed + error/kp;
//      if(lSpeed > 255) {
//        lSpeed = 255;
//      }
//    } else if (error < 0) {
//      //slave is faster than master
//      lSpeed = lSpeed + error/kp;
//      if(lSpeed < 0) {
//        lSpeed = 0;
//      }
//    }
//  }
  m.forward();
  kController();
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }

  Serial.print("Right : ");
  Serial.print(rSpeed);
  Serial.print("  Left : ");
  Serial.print(lSpeed);
  Serial.print("  Right : ");
  Serial.print(positionRight);
  Serial.print("  Left : ");
  Serial.println(positionLeft);

}
