#define PI 3.1415926535897932384626433832795

#include <math.h>

/*
   I reck y'all should get a move on.  Me and my campadres are gonna be ridin' through town
   soon and ya best be out of our way by then. (We are doing dead reckoning for some object avoidencs
   stuff)
*/

//distance between wheels in mm meters
//Wheel base of 212 was measured
//225 has the effects of barely overshooting turns
//235 has big overshoot
#define WHEEL_BASE 215
#define TICKS_PER_MM 21.561
//time between calculations in milliseconds
const int deltaT = 10;  //or 100 computations frames per second

/*
   This function is meant to be called to update the dead reckoning. Call
   it at set intervals and when we arrive or leave from a destination
   TODO MAYBE???? Make a yeeHawReset() function that rezeroes our position
   so we can run it again without the previous accumulated error.
*/
void yeeHaw() {
  lsamp = knobLeft.read();
  rsamp = knobRight.read();

  L_ticks = lsamp - last_left;
  R_ticks = rsamp - last_right;

  last_left = lsamp;
  last_right = rsamp;

  left_mm = (float) L_ticks / TICKS_PER_MM;
  right_mm = (float) R_ticks / TICKS_PER_MM;

  mm = (left_mm + right_mm) / 2.0;

  theta += (right_mm - left_mm) / WHEEL_BASE;

  theta -= (float)((int)(theta / (2 * PI))) * 2 * PI;

  // Degrees conversion
  Y_pos += mm * cos(theta);
  X_pos += mm * sin(theta);

}

const int kp = 1;


void kController() {
  positionLeft += L_ticks;
  positionRight += R_ticks;
  long error = (positionRight - positionLeft) / kp;
  //If master is faster than slave

  lSpeed = lSpeed + error;
  if (lSpeed > 255) {
    lSpeed = 255;
  } else if (lSpeed < 190) {
    lSpeed = 190;
  }

  //  Serial.print("Left Speed  ");
  //  Serial.print(lSpeed);
  //  Serial.print("  Right Speed  ");
  //  Serial.print(rSpeed);
  //  Serial.print("  Left  ");
  //  Serial.print(positionLeft);
  //  Serial.print("  Right  ");
  //  Serial.println(positionRight);
  //


  m.setRightMotorSpeed(rSpeed);
  m.setLeftMotorSpeed(lSpeed);

  /*
     I might need to add something here to reset the encoder
     counts once they exceed a certain amount.  Read in both values
     subtract and write 0 in one encoder and the difference in the other
  */
}


void goodTurn(float theRad, int theDir) {
  //  theta += (right_mm - left_mm) / WHEEL_BASE;
  float targetPos = 0;
  //LEFT IS NEGATIVE
  //RIGHT IS POSITIVE
  m.setRightMotorSpeed(0);
  rSpeed = 0;
  m.setLeftMotorSpeed(0);
  lSpeed = 0;
  if (theDir < 0) {
    //GO LEEEEEFT
    theRad = theRad * -1;
  }
  else {
    theRad = theRad;
  }

  /*
     I need to run a conversion on the radian distance to wheel ticks,
     then ensure that both wheel ticks are going the same amount by the end
  */
//  double targetTicks = 0;
//  targetTicks = fabs(theRad * TICKS_PER_MM * WHEEL_BASE / 2);

  //  L_ticks = lsamp - last_left;
  //  R_ticks = rsamp - last_right;
  //  double leftTicks = knobLeft.read();
  //  double rightTicks = knobRight.read();

  //  int flagL = 0;
  //  int flagR = 0;
  //  int finished = 0;
  //FOAM CUTTER BRING IT
  //BOX CUTTER BACK UP PLAN
  /*
    while (finished < 1) {

      if(theRad < 0) {
        //turn left stuff
        m.setLeftMotorDirection(1);
        m.setRightMotorDirection(1);
        leftTicks += abs(L_ticks);
        rightTicks += abs(R_ticks);
        if(leftTicks >= targetTicks){
          m.setLeftMotorSpeed(0);
          flagL = 1;

        }

        if(rightTicks >= targetTicks) {
          m.setRightMotorSpeed(0);
          flagR = 1;

        }

        if(flagR + flagL == 2){
          finished = 100;
          m.allStop();
        }

      }else{
        //RIGHT TURN NERD
        m.setLeftMotorDirection(0);
        m.setRightMotorDirection(0);
        leftTicks += abs(L_ticks);
        rightTicks += abs(R_ticks);
        if(leftTicks >= targetTicks){
          m.setLeftMotorSpeed(0);
          flagL = 1;

        }

        if(rightTicks >= targetTicks) {
          m.setRightMotorSpeed(0);
          flagR = 1;
        }

        if(flagR + flagL == 2){
          finished = 100;
          m.allStop();
        }
      }
      yeeHaw();
      delay(20);

      Serial.print(leftTicks);
      Serial.print("    ");
      Serial.println(rightTicks);
  */
  //  }
  if (theRad < 0) {
    m.turnLeft();
  } else {
    m.turnRight();
  }
  yeeHaw();
  //DumbMotorStart();
  while (fabs(targetPos) < fabs(theRad)) {

    delay(10);
    if(rSpeed < 220){
      DumbMotorStart();
    }
    yeeHaw();
    targetPos += (right_mm - left_mm) / WHEEL_BASE;
    //    Serial.println(targetPos);
    //    Serial.print("    ");
    //    Serial.println(theRad);



  }

  yeeHaw();

  //    Serial.print(targetTicks);
  //    Serial.print("    ");
  //    Serial.println(theRad);
}

void gotoCoordinate(double theX, double theY) {
  double oldTheta = theta;
  turnToZero();

  //1) Orientate towards the point
  // The front of the robot must be pointed at the destination.
  // This can be done by doing an inverse tangent on the two distances xd and yd
  //2) Get the distance to the point this is just pythagorean
  double xd = theX - X_pos;
  double yd = theY - Y_pos;
  yeeHaw();

  double targetDis = sqrt(xd * xd + yd * yd);
  double targetAngle = fabs(atan(xd / yd));

  //  Serial.print("THE TARGET IS ");
  //  Serial.print(targetDis);
  //  Serial.print("  THE ANGLE IS ");
  //  Serial.println(targetAngle);

  int quad = 0;
  if (theX >= X_pos && theY >= Y_pos) {
    quad = 1;
  } else if (theX <= X_pos && theY >= Y_pos) {
    quad = 2;
  } else if ( theX <= X_pos && theY <= Y_pos) {
    quad = 3;
    targetAngle = PI - targetAngle;
  } else {
    quad = 4;
    targetAngle = PI - targetAngle;
  }
  //  Serial.print("THE QUADRANT IS ");
  //  Serial.println( quad);
  double traveled = 0;
  //SPECIAL CASES
  //Based on the quadrent we do 4 things:
  //  The right 2 quadrants are turn rights
  //  The left 2 quadrants are turn left
  //  The top two quadrants are normal turns
  //  The bottom two quadrents are 180 degrees (OR PI radians) minus the desired angle.

  //Once the case is decided, we move to execution
  //  1) Turn the requested degrees in the correct direction based on our turn function
  if ( quad == 2 || quad == 3) {
    goodTurn(targetAngle, -1);
  } else if (quad == 1 || quad == 4) {
    goodTurn(targetAngle, 1);
  }
  m.allStop();
  xd = theX - X_pos;
  yd = theY - Y_pos;

  targetDis = sqrt(xd * xd + yd * yd);

  //FUDGE POWERS ACTIVATE
  if(theX != 0 && theY != 0){
        //targetDis = 750;
        targetDis = targetDis + 150;
  }

  
  //  2) Go forward in the specified distance first set the speed to zero, then
  //     using m.forward, dumbMotorStart, kcontroller, and yeehaw(). call yeehaw()
  //     after the dumbMotorStart and again at 50 ms delayed intervals to keep checking if we
  //     have gone the specified distance
  m.setRightMotorSpeed(0);
  rSpeed = 0;
  m.setLeftMotorSpeed(0);
  lSpeed = 0;
  m.forward();
  yeeHaw();
  traveled += mm;
  while ( traveled < targetDis) {

    delay(10);
    yeeHaw();
    DumbMotorStart();
    traveled += mm;
    if (rSpeed >= 190) {
      kController();
    }
    //      Serial.print("Left  ");
    //  Serial.print(positionLeft);
    //  Serial.print("  Right  ");
    //  Serial.println(positionRight);
    //

  }
  //  Serial.print("X = ");
  //  Serial.print(X_pos);
  //  Serial.print("  Y = ");
  //  Serial.print(Y_pos);
  //  Serial.print(" Theta = ");
  //  Serial.println(theta);
  m.allStop();
  positionLeft = 0;
  positionRight = 0;

}




//SUPPOSED TO BE A SMART TURN BUT IT SUCKS
void TurnAngle(float theRad) {
  //  Serial.println(theRad);
  float targetPos = theta + theRad;
  float currentPos = theta;
  while (targetPos > 2 * PI) {
    targetPos -= 2 * PI;
  }
  while (targetPos < -2 * PI) {
    targetPos += 2 * PI;
  }
  float turnR = 2 * PI - theta + targetPos;
  float turnL = theta + targetPos;
  //  Serial.println(targetPos);

  if (turnR < turnL) {
    m.setRightMotorSpeed(255);
    m.setLeftMotorSpeed(255);
    while (targetPos > 0) {
      m.turnRight();
      targetPos = targetPos - currentPos;
      yeeHaw();
      currentPos = currentPos - theta;
      delay(50);
      //        Serial.print("X = ");
      //  Serial.print(X_pos);
      //  Serial.print("  Y = ");
      //  Serial.print(Y_pos);
      //  Serial.print(" Theta = ");
      //  Serial.println(theta);
    }
  } else if (turnL < turnR) {
    m.setRightMotorSpeed(255);
    m.setLeftMotorSpeed(255);
    while (targetPos < theta) {
      m.turnLeft();
      yeeHaw();
      delay(50);
      //        Serial.print("X = ");
      //  Serial.print(X_pos);
      //  Serial.print("  Y = ");
      //  Serial.print(Y_pos);
      //  Serial.print(" Theta = ");
      //  Serial.println(theta);
    }
  }
  m.setRightMotorSpeed(rSpeed);
  m.setLeftMotorSpeed(lSpeed);

}

void turnToZero() {
  if (theta > 0) {
    goodTurn(fabs(theta), -1);
  } else if ( theta < 0) {
    goodTurn(fabs(theta), 1);
  }
}

void DumbMotorStart() {
  if (lSpeed < 255) {
    lSpeed += 1;
    m.setLeftMotorSpeed(lSpeed);
  }

  if (rSpeed < 255) {
    rSpeed += 1;
    m.setRightMotorSpeed(rSpeed);
  }

}

void resetAll() {
  theta = 0;
  X_pos = 0;
  Y_pos = 0;
  positionLeft = 0;
  positionRight = 0;
  knobLeft.write(0);
  knobRight.write(0);
  lsamp = 0;
  rsamp = 0;
  L_ticks = 0;
  R_ticks = 0;
  last_left = 0;
  last_right = 0;
  left_mm = 0;
  right_mm = 0;
  mm = 0;
}

int readLine(int QRE1113_Pin) {
  pinMode(QRE1113_Pin, OUTPUT);
  digitalWrite(QRE1113_Pin, HIGH);
  delayMicroseconds(10);
  pinMode(QRE1113_Pin, INPUT);

  long time = micros();
  int diff = 0;
  //time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while (digitalRead(QRE1113_Pin) == HIGH && micros() - time < 3000) {
    diff = micros() - time;
  }
  return diff;

}

void lineFollow() {
  m.forward();

  while (readLine(linePinLeft) < lineThreshold) {
    /*
        Do some turning in the correct direction.
        we need to back up and turn right (which is heading left if you think of it like a car)
    */
    //m.slowTurn(0, 150, 255);
    m.turnLeft();
    delay(250);
  }

  while (readLine(linePinRight) < lineThreshold) {
    /*
        Do some turning in the correct direction.
        we need to back up and turn left (which makes you go right since we are backing up)
    */
    //m.slowTurn(0, 255, 150);
    m.turnRight();
    delay(600);
  }
  m.setRightMotorSpeed(245);
  m.setLeftMotorSpeed(250);
}

void fudgeBacker(double theFudge) {
  double traveled = 0;
  double targetDis = theFudge;
  m.setRightMotorSpeed(0);
  rSpeed = 0;
  m.setLeftMotorSpeed(0);
  lSpeed = 0;

  if(theFudge > 0){
    m.forward();
  }else{
  m.reverse();
  }
  while ( traveled < fabs(targetDis)) {

    delay(10);
    yeeHaw();
    if(lSpeed < 190){
    DumbMotorStart();
    }
    //if(theFudge > 0) {
    //  kController();
    //}
    traveled += fabs(mm);

  }
  m.allStop();
}
