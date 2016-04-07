#include "pwm.h"
#include "PID.h"
#include "Encoder.h"

void setLeftPwm(int speed) {
  if(speed > 999)//parameter check
		speed = 999;
	if(speed < -999)
		speed = -999;

    if(speed >= 0)//forward
    {
        L_PWM_F = speed;
        L_PWM_R	= 0;
    }
    else//rewind
    {
        L_PWM_F = 0;
        L_PWM_R	= -speed;
    }
}
void setRightPwm(int speed) {
  if(speed > 999)
		speed = 999;
	if(speed < -999)
		speed = -999;

    if(speed >= 0)//forward
    {
        R_PWM_F = speed;
        R_PWM_R	= 0;
    }
    else//rewind
    {
        R_PWM_F = 0;
        R_PWM_R	= -speed;
    }
}

void calculateMotorPwm(void) // encoder PD controller
{
	// int gyroFeedback;
	int rotationalFeedback;
	// int sensorFeedback;

    /* simple PD loop to generate base speed for both motors */
	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;

	// gyroFeedback = aSpeed/gyroFeedbackRatio; //gyroFeedbackRatio mentioned in curve turn lecture
	sensorFeedback = sensorError/a_scale;//have sensor error properly scale to fit the system

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

	posPwmX = kpX * posErrorX + kdX * (posErrorX - oldPosErrorX);
	posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);

	oldPosErrorX = posErrorX;
	oldPosErrorW = posErrorW;

	leftBaseSpeed = posPwmX - posPwmW;
	rightBaseSpeed = posPwmX + posPwmW;

	setLeftPwm(leftBaseSpeed);
	setRightPwm(rightBaseSpeed);
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
