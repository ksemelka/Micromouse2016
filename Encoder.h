#ifndef ENCODER_H
#define ENCODER_H

extern int leftEncoder;
extern int rightEncoder;

extern double encoderCount;
extern int leftEncoderCount;
extern int rightEncoderCount;

extern double encoderChange;
extern int leftEncoderChange;
extern int rightEncoderChange;

extern int leftEncoderOld;
extern int rightEncoderOld;
extern double distanceLeftX;
extern double distanceLeftW;
extern bool turningRight;

extern int oldEncoderCount;

void getEncoderStatus();
void resetRightEncCount();
void resetLeftEncCount();

#endif /*ENCODER_H*/
