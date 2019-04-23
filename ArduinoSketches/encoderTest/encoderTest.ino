/* Encoder Library - Basic Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

#include <Encoder.h>

// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability

//My two enc pins sets are 2,3 and 18,19
Encoder myEncL(2,3);
//   avoid using pins with LEDs attached

Encoder myEncR(18,19);

const float Circumference = 248.186;
const float Revolution = 4741.44;

void setup() {
  Serial.begin(57600);
  Serial.println("Basic Encoder Test:");
}

long oldPositionLeft  = -999;

long oldPositionRight = -999;

void loop() {
  long newPositionLeft = myEncL.read();
  long newPositionRight = myEncR.read();
  if (newPositionLeft != oldPositionLeft || oldPositionRight != newPositionRight) {
    oldPositionLeft = newPositionLeft;
    oldPositionRight = newPositionRight;
    Serial.print("Left Rotation: ");
    Serial.print(myEncL.read());
    Serial.print("Left Distance: ");
    Serial.print(newPositionLeft * Circumference / Revolution );
    Serial.print("   Right Rotation: ");
    Serial.print(myEncR.read());
    Serial.print("Right Distance: ");
    Serial.println(newPositionRight * Circumference / Revolution );
  }
}
