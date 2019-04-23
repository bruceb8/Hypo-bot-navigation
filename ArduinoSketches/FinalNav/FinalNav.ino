#include <motorDriver.h>
#include <Encoder.h>
#include <LobotServoController.h>

#define CAM_HEIGHT 330.2
#define FUDGE "I am a Cute Robot"
#define FUDGEBACK -90
#define TIME_TILL_SCAN 3000
LobotServoController xArm(Serial1);

int burgDog = 0;

float y = 16.4;
float d = 9.6;  //cm
float c = 16.5;

LobotServo Drop[6];
LobotServo idle[6];
LobotServo PreGrab[6];
LobotServo PostGrab[6];
LobotServo PostGrabTurn[6];
LobotServo OverBin[6];
LobotServo lookAhead[6];



// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder knobLeft(20, 21);
Encoder knobRight(3, 2);
//   avoid using pins with LEDs attached

//Motor A Left
const int motor1Pin1  = 30;  
const int motor1Pin2  = 12;  
const int motor1Speed = 11;

//Motor B Right
const int motor2Pin1  = 6; 
const int motor2Pin2  = 5;  
const int motor2Speed = 4;

motorDriver m(motor1Pin1, motor1Pin2, motor1Speed, motor2Pin1, motor2Pin2, motor2Speed);

const int linePinLeft = 10;
const int linePinRight = 7;

int lineThreshold = 80;

//Left motor seems faster so it will be the slave
int lSpeed = 245;

//Right motor is the master "MATCH ME" SCREAMS THE RIGHT SIDE
int rSpeed = 245;

double theta = 0;
double X_pos = 0;
double Y_pos = 0;


double lsamp = 0, rsamp = 0, L_ticks = 0, R_ticks = 0, last_left = 0, last_right = 0;
double left_mm = 0, right_mm, mm = 0;

double positionLeft  = 0;
double positionRight = 0;

//The X value (left or right AKA ROBOT X VALUE)
double state = -2;

//The Y value (height off the ground)
double state1 = -2;

//The Z value (The distance AKA ROBOT Y VALUE)
double state2 = -2;
char ch = 0;


void setup() {
  //Change the serial value to whatever the pi needs
  Serial.begin(9600);
  Serial1.begin(9600);
  // put your setup code here, to run once:
  actionsets();
  GIT(18, 0);
  /*
  m.setRightMotorSpeed(125);
  m.setLeftMotorSpeed(125);
  m.forward();
  delay(10000);
  */



}

unsigned long currentTime = 0;

void loop() {
  //testFunction();

  
  // put your main code here, to run repeatedly:
  /*
     Heres the general idea on what steps we take when
      1)We need to start with following the line.  We just repeat the call
      to line follow all the time, we just run it in a while loop while checking the time

      2) When a certain amount of time passes, we do a "scan" with the camera
        2a)To do the scan, we first reset all of our odometry numbers (using resetAll or whatever)
        2b)Then since we are goin COUNTERCLOCKWISE around the track, we only have to look to the right
        or forward, so we only scan forward, turn PI/2 to the right and scan again. We wait for 5 seconds
      3)If we find nothing, we call turnToZero() and go back to line following
      OR
      4)We find something and recieve from getCoords()
      5)We go to the sent coordinates
      6)Since we plan to overshoot everything we back up BENEN_ARM_AMOUNT to consistantly place the syringe
        at a consistant location in front of the robot
      7)Call GIT at the BENEN_ARM_AMOUNT
      8)Go back to home and stop the motors
      9)Reorientate towards track
      10)Clear out the buffer
      11)Reset the state variables

  */
  //LINE FOLLOW AND SET START TIME
  currentTime = millis();
  unsigned long passedTime = millis();
  while ( passedTime - currentTime < TIME_TILL_SCAN) {
    passedTime = millis();
    lineFollow();
  }
  m.allStop();
  //Begin Scane procedure
  //First we reset everything we read in before accidently with the endcoders and previous runs
  

  //then we do a short delay to give the PI time to find the syringe
//  getCoords();
//  //if we found something, then we go to it!
//  if (state != -4 && state1 != -2 && state2 != 0) {
//    state2 = sqrt(state2 * state2 + pow(CAM_HEIGHT - state1, 2));
//    gotoCoordinate((double)state, (double) state2);
//    fudgeBacker();
//    GIT(13, 69);
//    gotoCoordinate(0, 0);
//    turnToZero();
//    m.allStop();
//    clearBuffer();
//    state = -4;
//    state = -2;
//    state = 0;
//  }
//we scan here
  
//    resetAll();
//    goodTurn(1.57079632679, 1);
//    m.allStop();
//    resetAll();
  
  clearBuffer();
  delay(1500);
  getCoords();
  //if we found something, then we go to it!
  if (state != -39 && state1 != -2 && state2 != 0) {
    
    resetAll();
    goodTurn(PI/2, 1);
    m.allStop();
    resetAll();
    FaceForward();
    delay(1500);
    clearBuffer();
    delay(1500);
    //state2 = sqrt(state2 * state2 + pow(CAM_HEIGHT - state1, 2));
    double tempX = state;
    double tempY = state2;
    getCoords();
    if(state == -39){
      state = tempX + 65;
      state2 = tempY + 50;
    }
    
    double fudgeAngle = atan(state / state2);
//    theta = 0;
//    yeeHaw();
    gotoCoordinate((double)state, (double) state2);
    double tempTheta = theta;
    for( int i = 0; i < 1; i++){
      goodTurn(PI/4, 1);
      goodTurn(PI/2, -1);
      goodTurn(PI/4, 1);
    }
    //fudgeBacker(100);
    fudgeBacker(FUDGEBACK);
    clearBuffer();
    delay(1500);
    
    getCoords();
    
    
    fudgeBacker(60);
    GIT(18, burgDog);

    gotoCoordinate(0, 0);
    turnToZero();
//    fudgeBacker(-20);
    m.allStop();
    clearBuffer();
    state = -39;
    state = -2;
    state = 0;
    burgDog = 0;
    goodTurn(1.57079632679 + fudgeAngle, -1);
    m.allStop();
    delay(500);
    resetAll();
  }



}


/*
   FOR A TEST WE JUST IDLE AROUND UNTIL WE GET THE COORDINATES FROM THE PI
*/



//
//void testFunction(){
//
//   delay(5000);
//   getCoords();
//   if(state != -4 && state1 != -2 && state2 != 0){
//    state2 = sqrt(state2*state2 + pow(CAM_HEIGHT - state1,2));
//    resetAll();
//
//    gotoCoordinate((double)state,(double) state2);
//    delay(1000);
//
//    //AdjustCamera to position camera above target zone
//    //Then we getCoords() again
//    //then we feed the appropriate values into GIT
//    GIT(13,69);
//    gotoCoordinate(0,0);
//    delay(100);
//    turnToZero();
//    m.allStop();
//    clearBuffer();
//
//   }
//    state = -4;
//    state1 = -2;
//    state2 = 0;
//}
