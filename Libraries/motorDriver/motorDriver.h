/*
	motorDriver.h Library for controlling the motors
	in the TCES460 2019 Hypo Bot Project
	Bruce Baker, Feb 4, 2019
	Released into the public domain

*/

#ifndef motorDriver_h
#define motorDriver_h

#include "Arduino.h"

class motorDriver{
	public:
		motorDriver(int m1Pin1, int m1Pin2, int leftSpeed, int m2Pin1, int m2Pin2, int rightSpeed);
		void setLeftMotorDirection(int direction);
		void setRightMotorDirection(int direction);
		
		void forward();
		void reverse();
		void turnRight();
		void turnLeft();
		
		void slowTurn(int direction, int left, int right);
		
		/*
		The following fucntions use the encoder to try to do some precise manueruvers
		*/
		void turnDeg(float theDeg);
		void forMMeters(float theMet);
		void revMMeters(float theMet);
		
		void stopLeftMotor();
		void stopRightMotor();
		void setLeftMotorSpeed(int speed);
		void setRightMotorSpeed(int speed);
		int getLeftMotorSpeed();
		int getRightMotorSpeed();
		void allStop();
	private:
		int _leftDirection;
		int _rightDirection;
		int _m1Pin1;
		int _m1Pin2;
		int _m2Pin1;
		int _m2Pin2;
		int _leftSpeedPin;
		int _rightSpeedPin;
		int _lSpeed;
		int _rSpeed;
		
		/* encoder pins */
		int lenc1;
		int lenc2;
		int renc1;
		int renc2;
	
};


#endif