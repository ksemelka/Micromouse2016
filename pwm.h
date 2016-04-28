#ifndef PWM_H
#define PWM_H
#include "Motors.h"
#include <Arduino.h>

#define turnMotorOff     setLeftPwm(0);setRightPwm(0)
#define turnMotorENOff      digitalWrite(LEFTMotorEN, LOW);digitalWrite(RIGHTMotorEN, LOW)
#define turnMotorENOn       digitalWrite(LEFTMotorEN, HIGH); digitalWrite(RIGHTMotorEN, HIGH)
#define MAXSPEEDX         72
#define GOODTARGETSPEEDX  65
#define TURNDISTANCE      2293

extern double accX;
extern double accW;
extern double decX;
extern double decW;
extern double curSpeedX;
extern double curSpeedW;
extern double targetSpeedX;
extern double targetSpeedW;
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

extern double kdX;
extern double kdW;

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

double speed_to_counts(double);
double counts_to_speed(double);
void setLeftPwm(int);
void setRightPwm(int);
void updateCurrentSpeed();
void calculateMotorPwm();
void moveOneCell();
int needToDecelerate(int, int, int);
void resetSpeedProfile();

// Movement:
void turnRightAndLeft();
void turnLeftEncoderTicks();
void turnRightEncoderTicks();
void goForwardAndBackward();
void goForwardDist(int dist);
void goBackwardDist(int dist);


#endif /*PWM_H*/
