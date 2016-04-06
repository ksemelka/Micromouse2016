#ifndef ENCODER_H
#define ENCODER_H

int leftEncoder;
int rightEncoder;

int encoderCount;
int leftEncoderCount;
int rightEncoderCount;

int encoderChange;
int leftEncoderChange;
int rightEncoderChange;

int leftEncoderOld;
int rightEncoderOld;
int distanceLeft;

void getEncoderStatus();
int getLeftEncCount();
int getRightEncCount();
void resetRightEncCount();
void resetLeftEncCount();

#endif /*ENCODER_H*/
