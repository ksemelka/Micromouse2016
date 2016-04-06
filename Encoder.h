#ifndef ENCODER_H
#define ENCODER_H

int leftEncoderCount;
int leftEncoderChange;
int rightEncoderCount;
int rightEncoderChange;
int distanceLeft;
int leftEncoderOld;
int rightEncoderOld;
int encoderCount;
int leftEncoder;
int rightEncoder;

void getEncoderStatus();
int getLeftEncCount();
int getRightEncCount();
void resetRightEncCount();
void resetLeftEncCount();

#endif /*ENCODER_H*/
