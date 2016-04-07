#ifndef PWM_H
#define PWM_H

#define turnMotorOff     setLeftPwm(0);setRightPwm(0)

int curSpeedX;
int curSpeedW;
int targetSpeedX;
int targetSpeedW;
int posErrorX;
int posErrorW;
int oldPosErrorX;
int oldPosErrorW;
int leftBaseSpeed;
int rightBaseSpeed;

void setLeftPwm(int);
void setRightPwm(int);
void calculateMotorPwm();
void resetSpeedProfile();

#endif /*PWM_H*/
