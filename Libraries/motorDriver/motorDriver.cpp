/*
	motorDriver Library for controlling the motors on the hypobot
	Bruce Baker, Feb 4, 2019
	
*/

#include "Arduino.h"
#include "motorDriver.h"
/*
Create the motorDriver object.  It takes in the 6(?) pins that will be used to control
the motor direction and the speed from the rotary encoder.
*/
motorDriver::motorDriver(int m1Pin1, int m1Pin2, int leftSpeed, int m2Pin1, int m2Pin2, int rightSpeed)
{	

	
	_m1Pin1 = m1Pin1;
	_m1Pin2 = m1Pin2;
	_m2Pin1 = m2Pin1;
	_m2Pin2 = m2Pin2;
	_leftSpeedPin = leftSpeed;
	_rightSpeedPin = rightSpeed;
	pinMode(_m1Pin1, OUTPUT);
	pinMode(_m1Pin2, OUTPUT);
	pinMode(_m2Pin1, OUTPUT);
	pinMode(_m2Pin2, OUTPUT);
	pinMode(_rightSpeedPin, OUTPUT);
	pinMode(_leftSpeedPin, OUTPUT);
}

/*
For the motor direction functions, 0 will be reverse (counterclockwise) and 1
will be the foward direction (clockwise)
*/
void motorDriver::setLeftMotorDirection(int direction){
	if( direction == 1) {
		digitalWrite(_m1Pin1, HIGH);
		digitalWrite(_m1Pin2, LOW);
	} else if(direction == 0) {
		digitalWrite(_m1Pin1, LOW);
		digitalWrite(_m1Pin2, HIGH);
	}
		
}




void motorDriver::forward() {
	digitalWrite(_m1Pin1, LOW);
	digitalWrite(_m1Pin2, HIGH);
	digitalWrite(_m2Pin1, HIGH);
	digitalWrite(_m2Pin2, LOW);	
}

void motorDriver::reverse() {
	digitalWrite(_m1Pin1, HIGH);
	digitalWrite(_m1Pin2, LOW);
	digitalWrite(_m2Pin1, LOW);
	digitalWrite(_m2Pin2, HIGH);

}


void motorDriver::turnRight() {
	digitalWrite(_m1Pin1, LOW);
	digitalWrite(_m1Pin2, HIGH);
	digitalWrite(_m2Pin1, LOW);
	digitalWrite(_m2Pin2, HIGH);
}

void motorDriver::turnLeft() {
	digitalWrite(_m1Pin1, HIGH);
	digitalWrite(_m1Pin2, LOW);
	digitalWrite(_m2Pin1, HIGH);
	digitalWrite(_m2Pin2, LOW);
}

/*
	direction 1 = forward, 0 = reverse
*/

void motorDriver::slowTurn(int direction, int left, int right) {
	setLeftMotorSpeed(left);
	setRightMotorSpeed(right);
	
	
	
	if( direction == 1) {
		digitalWrite(_m1Pin1, LOW);
		digitalWrite(_m1Pin2, HIGH);
		digitalWrite(_m2Pin1, HIGH);
		digitalWrite(_m2Pin2, LOW);
	} else {
		digitalWrite(_m1Pin1, HIGH);
		digitalWrite(_m1Pin2, LOW);
		digitalWrite(_m2Pin1, LOW);
		digitalWrite(_m2Pin2, HIGH);
	}
	
}

void motorDriver::setRightMotorDirection(int direction){
	if( direction == 1) {
		digitalWrite(_m2Pin1, HIGH);
		digitalWrite(_m2Pin2, LOW);
	} else if(direction == 0) {
		digitalWrite(_m2Pin1, LOW);
		digitalWrite(_m2Pin2, HIGH);
	}
		
}

/*
	Setting the pins to the same value LOW OR HIGH will stop the motor
	
*/
void motorDriver::stopLeftMotor(){
	digitalWrite(_m1Pin1, LOW);
    digitalWrite(_m1Pin2, LOW);
}
void motorDriver::stopRightMotor(){
	digitalWrite(_m2Pin1, LOW);
    digitalWrite(_m2Pin2, LOW);
}


void motorDriver::allStop(){
	digitalWrite(_m1Pin1, LOW);
    digitalWrite(_m1Pin2, LOW);
	digitalWrite(_m2Pin1, LOW);
    digitalWrite(_m2Pin2, LOW);
}
/*
	The following functions are going to have to deal with the rotary encoders
	documentation.
*/
void motorDriver::setLeftMotorSpeed(int speed){
	analogWrite(_leftSpeedPin, speed);
	_lSpeed = speed;
	
}
void motorDriver::setRightMotorSpeed(int speed){
	analogWrite(_rightSpeedPin, speed);
	_rSpeed = speed;
	
}
int motorDriver::getLeftMotorSpeed(){
	return _lSpeed;
}
int motorDriver::getRightMotorSpeed(){
	return _rSpeed;
}







