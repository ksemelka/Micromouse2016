#include "Encoder.h"

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;

void resetRightEncCount() {
  noInterrupts();
  encoderValueLeft = 0;
  interrupts();
}
void resetLeftEncCount() {
  noInterrupts();
  encoderValueRight = 0;
  interrupts();
}

void getEncoderStatus() {
	leftEncoder = TIM2->CNT;//read current encoder ticks from register of 32 bit general purpose timer 2
	rightEncoder = TIM5->CNT;//read current encoder ticks from register of 32 bit general purpose timer 5

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
