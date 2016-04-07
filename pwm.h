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

int speed_to_counts(int);

int moveSpeed = speed_to_counts(500*2);
int turnSpeed = speed_to_counts(500*2);
int returnSpeed = speed_to_counts(500*2);
int stopSpeed = speed_to_counts(100*2);
int maxSpeed = speed_to_counts(2000*2);


int counts_to_speed(int);
void setLeftPwm(int);
void setRightPwm(int);
void updateCurrentSpeed();
void calculateMotorPwm();
int needToDecelerate(int, int, int);
void resetSpeedProfile();

#endif /*PWM_H*/
