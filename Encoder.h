#ifndef ENCODER_H
#define ENCODER_H

extern int leftEncoder;
extern int rightEncoder;

extern int encoderCount;
extern int leftEncoderCount;
extern int rightEncoderCount;

extern int encoderChange;
extern int leftEncoderChange;
extern int rightEncoderChange;

extern int leftEncoderOld;
extern int rightEncoderOld;
extern int distanceLeft;

// extern int oldEncoderCount;

void getEncoderStatus();
void resetRightEncCount();
void resetLeftEncCount();

#endif /*ENCODER_H*/
