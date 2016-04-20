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
  *Implement pidInputX and pidInputW
  *Fix needToDecelerate return statement
*/

extern Motors motors;
extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

double accX = 100;
double accW = 1;
double decX = 100;
double decW = 1;
double curSpeedX;
double curSpeedW;
double targetSpeedX;
double targetSpeedW;
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
int oneCellDistance = 1475; // in counts
int moveSpeed = speed_to_counts(500*2);
int turnSpeed = speed_to_counts(500*2);
int returnSpeed = speed_to_counts(500*2);
int stopSpeed = speed_to_counts(100*2);
int maxSpeed = speed_to_counts(2000*2);

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
      analogWrite(motors.LEFTlogic1, speed);
      analogWrite(motors.LEFTlogic2, 0);
    }
    else//backward
    {
      analogWrite(motors.LEFTlogic1, 0);
      analogWrite(motors.LEFTlogic2, -speed);
    }
}
void setRightPwm(int speed) {
  if(speed > 255)
		speed = 255;
	if(speed < -255)
		speed = -255;

  if(speed >= 0)//forward
  {
    analogWrite(motors.RIGHTlogic1, 0);
    analogWrite(motors.RIGHTlogic2, speed);
  }
  else//backward
  {
    analogWrite(motors.RIGHTlogic1, -speed);
    analogWrite(motors.RIGHTlogic2, 0);
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

void moveOneCell()
{
	enable_sensor(),
	enable_gyro();
	enable_PID();

	targetSpeedW = 0;
	targetSpeedX = moveSpeed;

	do
	{
		/*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
		here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
		/*sample*/
		if(needToDecelerate(distanceLeft, curSpeedX, moveSpeed) < decX)
			targetSpeedX = maxSpeed;
		else
			targetSpeedX = moveSpeed;

		//there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
	}
	while( ( (encoderCount-oldEncoderCount) < oneCellDistance && LFSensor < LFvalue2 && RFSensor < RFvalue2)//use encoder to finish 180mm movement if no front walls
	|| (LFSensor < LFvalues1 && LFSensor > LFvalue2)//if has front wall, make the mouse finish this 180mm with sensor threshold only
	|| (RFSensor < RFvalue1 && RFSensor > RFvalve2)
	);
	//LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
	//LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
	//and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
	//these thresholds just in case the readings are too weak.

	oldEncoderCount = encoderCount;	//update here for next movement to minimized the counts loss between cells.
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
