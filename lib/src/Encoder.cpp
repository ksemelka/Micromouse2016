#include "../inc/Encoder.h"

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

int leftEncoder;
int rightEncoder;

double encoderCount;
int leftEncoderCount;
int rightEncoderCount;

double encoderChange;
int leftEncoderChange;
int rightEncoderChange;

int leftEncoderOld;
int rightEncoderOld;
double distanceLeftX;
double distanceLeftW;
bool turningRight = false;

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
	encoderChange = (double)(leftEncoderChange + rightEncoderChange)/2;

	leftEncoderOld = leftEncoder;
	rightEncoderOld = rightEncoder;

	leftEncoderCount += leftEncoderChange;
	rightEncoderCount += rightEncoderChange;
	encoderCount =  (double)(leftEncoderCount+rightEncoderCount)/2;

	distanceLeftX -= encoderChange;// update distanceLeft
  if (turningRight) {
    distanceLeftW -= leftEncoderChange - rightEncoderChange;
  }
  else {
    distanceLeftW -= rightEncoderChange - leftEncoderChange;
  }
}
