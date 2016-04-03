#ifndef PID_H
#define PID_H
#include "PIDencoders.h"
#define VELOCITY_SAMPLE_TIME 100000  // Micros

/******************************************************************************************************
class PID {
  public:
    PID(double*, double*, double*,        // * Constructor. Links the PID to the Input, Output, and
        double, double, double);          //   Setpoint. Tuning parameters are also set here.

    bool Compute();                       // * Performs the PID calculation. It should be
                                          //   called every time loop() cycles.

  private:
    void SetTunings(double, double, double);  // Used in constructor

    double kp;        // Proportional tuning value
    double ki;        // Integral tuning value
    double kd;        // Derivative tuning value

    double* myInput;              // * Pointers to the Input, Output, and Setpoint variables.
    double* myOutput;             //   This creates a hard link between the variables and the
    double* mySetpoint;           //   PID, freeing the user from having to constantly tell us
                                  //   what these values are. With pointers we'll just know.

    unsigned long lastTime;
    double ITerm, lastInput;
    const double outMin = 0, outMax = 255;
    unsigned long SampleTime = 100.0;
};
*******************************************************************************************************/

class PID {
  public:
    PID(double, double, double);
    int calculateError();
    int calculateErrorSensors();
    double calculateProportionalEncoderError();
    void calculateVelocity();
//  private:
    void SetTunings(double, double, double);  // Used in constructor
    double kp;
    double ki;
    double kd;
    double velocityLeft = 0.0;
    double velocityRight = 0.0;
    double prevVelocityLeft = 0.0;
    double prevVelocityRight = 0.0;
    const double Kx = .8;      // FIXME: add proportional tuning value for encoders
    double encoderErrorLeft = 0.0;
    double encoderErrorRight = 0.0;
    double encoderErrorBoth = 0.0;

    double ITerm;
    unsigned long SampleTime = 100.0;
};

#endif /*PID_H*/
