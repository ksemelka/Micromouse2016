#include "Encoder.h"

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

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

int oldEncoderCount;

void resetRightEncCount() {
  encoderValueLeft = 0;
}
void resetLeftEncCount() {
  encoderValueRight = 0;
}

void getEncoderStatus() {
	leftEncoder = encoderValueLeft;
	rightEncoder = encoderValueRight;

	leftEncoderChange = leftEncoder - leftEncoderOld;
	rightEncoderChange = rightEncoder - rightEncoderOld;
	encoderChange = (leftEncoderChange + rightEncoderChange)/2;

	leftEncoderOld = leftEncoder;
	rightEncoderOld = rightEncoder;

	leftEncoderCount += leftEncoderChange;
	rightEncoderCount += rightEncoderChange;
	encoderCount =  (leftEncoderCount+rightEncoderCount)/2;

	distanceLeft -= encoderChange;// update distanceLeft
}
