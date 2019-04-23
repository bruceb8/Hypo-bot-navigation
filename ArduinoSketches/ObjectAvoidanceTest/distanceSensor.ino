/*
 * I need to figure out the encoders. It would be way simpler if I could tell the motors
 * to go a distance.  This can probably be done with the rotary encoder if it keeps track
 * of wheel rotations.  ODOMETRY HO
 * 
 * 
 */ 
#define PI 3.1415926535897932384626433832795



/*
 * I reck y'all should get a move on.  Me and my campadres are gonna be ridin' through town
 * soon and ya best be out of our way by then. (We are doing dead reckoning for some object avoidencs
 * stuff)
 */

//distance between wheels in meters
#define WHEEL_BASE .212
#define TICKS_PER_MM 21.561
//time between calculations in milliseconds
const int deltaT = 50;  //or 20 computations frames per second

float theta;
float X_pos;
float Y_pos;


int lsamp, rsamp, L_ticks, R_ticks, last_left, last_right;
float left_mm, right_mm, mm;

/*
 * This function is meant to be called to update the dead reckoning. Call
 * it at set intervals and when we arrive or leave from a destination
 * TODO MAYBE???? Make a yeeHawReset() function that rezeroes our position
 * so we can run it again without the previous accumulated error.
 */
void yeeHaw() {
  lsamp = knobLeft.read();
  rsamp = knobRight.read();

  L_ticks = lsamp - last_left;
  R_ticks = rsamp - last_right;

  last_left = lsamp;
  last_right = rsamp;
  
  left_mm = (float) L_ticks/TICKS_PER_MM;
  right_mm = (float) R_ticks/TICKS_PER_MM;

  mm = (left_mm + right_mm) / 2.0;

  theta += (left_mm - right_mm) / WHEEL_BASE;

  theta -= (float)((int)(theta/(2*PI)))*2*PI;

  Y_pos += mm * cos(theta);
  X_pos += mm * sin(theta);
  

}



const float Circumference = 219.91148;
const float Revolution = 4741.44;

void goDistance(long theDis) {
  //theDis is the input in millimeters
  
  //First we convert that into encoder ticks
  long target = theDis * Revolution / Circumference; 
  //Second we reset the encoders (woops said this one twice)

  //Third stop the motors and add a small delay to stop the
  //encoder count
  m.allStop();
  delay(100);
  //Fourth we zero out the encoders with enc.write(0)
    knobLeft.write(0);
    knobRight.write(0);
  //Fifth we change the speed to whatever even motion is for
  //Our motor.
  m.setRightMotorSpeed(MESpeedRight);
  m.setLeftMotorSpeed(MESpeedLeft);
  long traveledTicks = 0;
  //Sixth we run object detection until we get find an object
  while(traveledTicks < target){
    if(readDistance(lDPin) < 20) {
    //Do something
    }else if(readDistance(rDPin) < 20) {
    //Do something
    }else {
      //just increment the travel ticks accordingly
      traveledTicks += (knobLeft.read() + knobRight.read())/2;
  }

  //When we find an object we start a partially recursive routine
  //to avoid the object
    //First we turn the robot in the direction of the of sensor
    //that did not pick up the object

    //Second we drive forward a distance ~15cm to go past the object
    //Double check this number some triangle math

    //Third we turn back (again with a triangle angle) to put
    //us back on the original path

    //Fourth we turn back the opposite direction of the first turn
    //in order to orientate ourselves back on the original path

    //Then we subtract the total amount of distance we need traveled
    //by the amount we did (base this on triangles too)
  }
  
}

float readDistance( int pin) {
    float readVal = analogRead(pin);
    float volts = readVal;
    volts = volts * 5 / 1024;

  //  float distance = 13 * pow(volts, -1)*2.54;
  
  //http://qqtrading.com.my/infrared-proximity-sensor-10-80cm-sharp-gp2y0a21yk0f
  //Conversion factor taken from link above.
    
    float distance = 4800/(readVal - 20);
    if(distance < 0 || distance > 80) {
      distance = 0;
    }
    return distance;
}
