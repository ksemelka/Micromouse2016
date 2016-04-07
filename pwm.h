#ifndef PWM_H
#define PWM_H

#define turnMotorOff     setLeftPwm(0);setRightPwm(0)

extern int accX;
extern int accW;
extern int decX;
extern int decW;
extern double curSpeedX;
extern double curSpeedW;
extern int targetSpeedX;
extern int targetSpeedW;
extern int posPwmX;
extern int posPwmW;
extern double posErrorX;
extern double posErrorW;
extern double oldPosErrorX;
extern double oldPosErrorW;
extern int leftBaseSpeed;
extern int rightBaseSpeed;
extern int encoderFeedbackX;
extern int encoderFeedbackW;

void setLeftPwm(int);
void setRightPwm(int);
void calculateMotorPwm();
void resetSpeedProfile();

#endif /*PWM_H*/
