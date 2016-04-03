#ifndef PIDENCODERS_H
#define PIDENCODERS_H
#define SAMPLE_TIME 10000  // Micros

double velocityLeft = 0.0;
double velocityRight = 0.0;
double prevVelocityLeft = 0.0;
double prevVelocityRight = 0.0;
const double Kx = .2;      // FIXME: add proportional tuning value for encoders
double encoderErrorLeft = 0.0;
double encoderErrorRight = 0.0;
double encoderErrorBoth = 0.0;

double calculateProportionalEncoderError();
void calculateVelocity();

#endif /*PIDENCODERS_H*/
