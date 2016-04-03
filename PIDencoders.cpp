#include "PIDencoders.h"

extern int encoderLeftTicksPerSample;
extern int encoderRightTicksPerSample;
extern int encoderValueLeft;
extern int encoderValueRight;

void calculateVelocity() {
  velocityLeft = (double)encoderLeftTicksPerSample / SAMPLE_TIME;
  velocityRight = (double)encoderRightTicksPerSample / SAMPLE_TIME;
  calculateProportionalEncoderError();
  prevVelocityLeft = velocityLeft;  // Keep these values for calculating error
  prevVelocityRight = velocityRight;
}

double calculateProportionalEncoderError() {
  encoderErrorBoth = velocityRight - velocityLeft;
  return encoderErrorBoth * Kx;
}
