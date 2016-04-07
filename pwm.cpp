#include "pwm.h"
#include "PID.h"
#include "Encoder.h"
#include "Motors.h"
#include <cmath>
#include <Arduino.h>

/*Need to make:
  *UpdateCurrentSpeed()
  *Implement Old Encoder count in Motors.cpp
  *Implement PosPwmX and PosPwmW
  *speedToCounts()
*/

extern Motors motors;
extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

int accX;
int accW;
int decX;
int decW;
double curSpeedX;
double curSpeedW;
int targetSpeedX;
int targetSpeedW;
int posPwmX;
int posPwmW;
double posErrorX;
double posErrorW;
double oldPosErrorX;
double oldPosErrorW;
int leftBaseSpeed;
int rightBaseSpeed;
int encoderFeedbackX;
int encoderFeedbackW;

int speed_to_counts(int speed) {  // counts per mm  TODO
  return speed / 1000;
}
int counts_to_speed(int counts) { // counts per ms
  return counts * 1000;
}

void setLeftPwm(int speed) {
  if(speed > 255)//parameter check
		speed = 255;
	if(speed < -255)
		speed = -255;

    if(speed >= 0)//forward
    {
      digitalWrite(motors.LEFTlogic1, HIGH);
      digitalWrite(motors.LEFTlogic2, LOW);
      analogWrite(motors.LEFTMotorEN, speed);
    }
    else//backward
    {
      digitalWrite(motors.LEFTlogic1, LOW);
      digitalWrite(motors.LEFTlogic2, HIGH);
      analogWrite(motors.LEFTMotorEN, -speed);
    }
}
void setRightPwm(int speed) {
  if(speed > 255)
		speed = 255;
	if(speed < -255)
		speed = -255;

  if(speed >= 0)//forward
  {
    digitalWrite(motors.RIGHTlogic1, LOW);
    digitalWrite(motors.RIGHTlogic2, HIGH);
    analogWrite(motors.RIGHTMotorEN, speed);
  }
  else//backward
  {
    digitalWrite(motors.RIGHTlogic1, HIGH);
    digitalWrite(motors.RIGHTlogic2, LOW);
    analogWrite(motors.RIGHTMotorEN, -speed);
  }
}

void updateCurrentSpeed()
{
	if(curSpeedX < targetSpeedX)
	{
		// curSpeedX += (float)(speed_to_counts(accX*2)/100); TODO
		if(curSpeedX > targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	else if(curSpeedX > targetSpeedX)
	{
		// curSpeedX -= (float)speed_to_counts(decX*2)/100; TODO
		if(curSpeedX < targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	if(curSpeedW < targetSpeedW)
	{
		curSpeedW += accW;
		if(curSpeedW > targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	else if(curSpeedW > targetSpeedW)
	{
		curSpeedW -= decW;
		if(curSpeedW < targetSpeedW)
			curSpeedW = targetSpeedW;
	}
}

void calculateMotorPwm(void) // encoder PD controller
{
	// int gyroFeedback;
	int rotationalFeedback;
	// int sensorFeedback;

    /* simple PD loop to generate base speed for both motors */
	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW

	// gyroFeedback = aSpeed/gyroFeedbackRatio; //gyroFeedbackRatio mentioned in curve turn lecture
	// sensorFeedback = sensorError/a_scale;//have sensor error properly scale to fit the system TODO

	// if(onlyUseGyroFeedback)
	// 	rotationalFeedback = guroFeedback;
	// else if(onlyUseEncoderFeedback)
		rotationalFeedback = encoderFeedbackW;
	// else
	// 	rotationalFeedback = encoderFeedbackW + gyroFeedback;
	    //if you use IR sensor as well, the line above will be rotationalFeedback = encoderFeedbackW + gyroFeedback + sensorFeedback;
	    //make sure to check the sign of sensor error.

	posErrorX += curSpeedX - encoderFeedbackX;
	posErrorW += curSpeedW - rotationalFeedback;

	// posPwmX = kpX * posErrorX + kdX * (posErrorX - oldPosErrorX);
	// posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);

	oldPosErrorX = posErrorX;
	oldPosErrorW = posErrorW;

	leftBaseSpeed = posPwmX - posPwmW;
	rightBaseSpeed = posPwmX + posPwmW;

	setLeftPwm(leftBaseSpeed);
	setRightPwm(rightBaseSpeed);
}

int needToDecelerate(int dist, int curSpd, int endSpd)//speed are in encoder counts/ms, dist is in encoder counts
{
	if (curSpd<0) curSpd = -curSpd;
	if (endSpd<0) endSpd = -endSpd;
	if (dist<0) dist = 1;//-dist;
	if (dist == 0) dist = 1;  //prevent divide by 0

	return (abs(counts_to_speed((curSpd*curSpd - endSpd*endSpd)*100*(double)/dist/4/2))); //dist_counts_to_mm(dist)/2);
	//calculate deceleration rate needed with input distance, input current speed and input targetspeed to determind if the deceleration is needed
	//use equation 2*a*S = Vt^2 - V0^2  ==>  a = (Vt^2-V0^2)/2/S
	//because the speed is the sum of left and right wheels(which means it's doubled), that's why there is a "/4" in equation since the square of 2 is 4
}

void resetSpeedProfile(void)
{
	//resetEverything;

	// //disable sensor data collecting functions running in 1ms interrupt
 // 	useSensor = false;
 // 	useGyro = false;
	// //no PID calculating, no motor lock
	// usePID = false;

	setLeftPwm(0);
	setRightPwm(0);

	pidInputX = 0;
	pidInputW = 0;
	curSpeedX = 0;
	curSpeedW = 0;
	targetSpeedX = 0;
	targetSpeedW = 0;
	posErrorX = 0;
	posErrorW = 0;
	oldPosErrorX = 0;
	oldPosErrorW = 0;
  leftEncoderOld = 0;
	rightEncoderOld = 0;
	leftEncoder = 0;
	rightEncoder = 0;
	leftEncoderCount = 0;
	rightEncoderCount = 0;
	encoderCount = 0;
	oldEncoderCount = 0;
	leftBaseSpeed = 0;
	rightBaseSpeed = 0;

	encoderValueLeft = 0;//reset left encoder count
	encoderValueRight = 0;//reset right encoder count
}
