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
Encoder knobLeft(21, 20);
Encoder knobRight(2, 3);
//   avoid using pins with LEDs attached

//Motor A
const int motor1Pin1  = 13;  // Pin 14 of L293
const int motor1Pin2  = 12;  // Pin 10 of L293
const int motor1Speed = 11;

//Motor B
const int motor2Pin1  = 6; // Pin  7 of L293
const int motor2Pin2  = 5;  // Pin  2 of L293
const int motor2Speed = 4;

motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);

int lSpeed = 240;
int rSpeed = 255;

void setup() {
  Serial.begin(57600);
  Serial.println("TwoKnobs Encoder Test:");
  m.setRightMotorSpeed(rSpeed);
  m.setLeftMotorSpeed(lSpeed);
}

long positionLeft  = -999;
long positionRight = -999;

void loop() {
  m.forward();
  long newLeft, newRight;
  newLeft = knobLeft.read();
  newRight = knobRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    positionLeft = newLeft;
    if(positionLeft < 0) {
      positionLeft = positionLeft * -1;
    }
    positionRight = newRight;
    if(positionRight < 0) {
      positionRight = positionRight * -1;
    }
    Serial.print("Left = ");
    Serial.print(positionLeft);
    Serial.print(", Right = ");
    Serial.print(positionRight);
    Serial.println();

    if(positionLeft > positionRight) {
      Serial.print("Left is faster");
      lSpeed--;
      //rSpeed++;
      if(lSpeed > 255){
        lSpeed = 255;
      }
      if(rSpeed > 255){
        rSpeed = 255;
      }
      if(rSpeed > 255){
        rSpeed = 255;
      }
      if(lSpeed < 0){
        lSpeed = 0;
      }
      if(rSpeed < 0){
        rSpeed = 0;
      }
      m.setLeftMotorSpeed(lSpeed);
      m.setRightMotorSpeed(rSpeed);

      Serial.print("  Left Speed = ");
      Serial.print(lSpeed);
      Serial.print(" Right Speed = ");
      Serial.println(rSpeed); 
      
    }else if(positionLeft < positionRight) {
      Serial.print("Right is faster");
      lSpeed++;
      //rSpeed--;
      if(lSpeed > 255){
        lSpeed = 255;
      }
      if(rSpeed > 255){
        rSpeed = 255;
      }
      if(lSpeed < 0){
        lSpeed = 0;
      }
      if(rSpeed < 0){
        rSpeed = 0;
      }
      m.setLeftMotorSpeed(lSpeed);
      m.setRightMotorSpeed(rSpeed);

      Serial.print("  Left Speed = ");
      Serial.print(lSpeed);
      Serial.print(" Right Speed = ");
      Serial.println(rSpeed); 
      
    }else if(positionLeft <= 100 + positionRight && positionLeft >= positionRight - 100){
      Serial.print("EQUAL SPEED HYPE");
      Serial.print("  Left Speed = ");
      Serial.print(lSpeed);
      Serial.print(" Right Speed = ");
      Serial.println(rSpeed); 
    }

      
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both knobs to zero");
    knobLeft.write(0);
    knobRight.write(0);
  }
 delay(50);
}
