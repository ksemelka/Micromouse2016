#include "PID.h"
#include "State.h"
#include <Arduino.h>
//
// PID::PID(double* Input, double* Output, double* Setpoint, double Kp, double Ki, double Kd) {
//   myOutput = Output;
//   myInput = Input;
//   mySetpoint = Setpoint;
//
//   PID::SetTunings(Kp, Ki, Kd);
//
//   lastTime = millis() - SampleTime;
// }
//
// /* Compute() **********************************************************************
//  *   This function should be called every time "void loop()" executes. The function
//  *   will decide for itself whether a new pid Output needs to be computed.
//  *   Returns true when the output is computed, false when nothing has been done.
//  **********************************************************************************/
//
// bool PID::Compute() {
//   unsigned long now = millis();
//   unsigned long timeChange = (now - lastTime);
//   if (timeChange >= SampleTime) {
//      /*Compute all the working error variables*/
// 	   double input = *myInput;
//      double error = *mySetpoint - input;
//      ITerm += (ki * error);
//
//      if (ITerm > outMax) { ITerm = outMax; }
//      else if (ITerm < outMin) { ITerm = outMin; }
//
//      double dInput = (input - lastInput);
//
//      /*Compute PID Output*/
//      double output = kp * error + ITerm - kd * dInput;
//
// 	   if (output > outMax) { output = outMax; }
//      else if (output < outMin) { output = outMin; }
// 	   *myOutput = output;
//
//      /*Remember some variables for next time*/
//      lastInput = input;
//      lastTime = now;
// 	   return true;
//    }
//    else { return false; }
// }

PID::PID(double Kp, double Ki, double Kd) {
  PID::SetTunings(Kp, Ki, Kd);
  ITerm = 0;
}

int PID::calculateError() {
  int error = 0;
  sensors.readSensors();
  if (wallToTheRight() && wallToTheLeft()) {
    error = sensors.getRightSmoothed() - sensors.getLeftSmoothed();
  }
  else if (wallToTheRight() && !wallToTheLeft()) {
    error = targetSide - sensors.getRightSmoothed();
  }
  else if (wallToTheLeft() && !wallToTheRight()) {
    error = targetSide - sensors.getLeftSmoothed();
  }
  error *= kp;
  return error;
}

void PID::SetTunings(double Kp, double Ki, double Kd = 0) {
  double SampleTimeInSec = ((double)SampleTime) / 1000;
  kp = Kp;
  ki = Ki * SampleTimeInSec;
  kd = Kd / SampleTimeInSec;
}
