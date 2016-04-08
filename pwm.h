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
extern int oneCellDistance;

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

int speed_to_counts(int);
int counts_to_speed(int);
void setLeftPwm(int);
void setRightPwm(int);
void updateCurrentSpeed();
void calculateMotorPwm();
void moveOneCell();
int needToDecelerate(int, int, int);
void resetSpeedProfile();

#endif /*PWM_H*/
