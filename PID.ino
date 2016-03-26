#include "PID.h"

PID::PID(double* Input, double* Output, double* Setpoint, double Kp, double Ki, double Kd) {
  myOutput = Output;
  myInput = Input;
  mySetpoint = Setpoint;

  PID::SetTunings(Kp, Ki, Kd);

  lastTime = millis() - SampleTime;
}

bool PID::Compute() {

}

double PID::GetKp() const { return kp; }
double PID::GetKi() const { return ki; }
double PID::GetKd() const { return kd; }

void PID::SetTunings(double Kp, double Ki, double Kd) {
  double SampleTimeInSec = ((double)SampleTime) / 1000;
  kp = Kp;
  ki = Ki * SampleTimeInSec;
  kd = Kd / SampleTimeInSec;
}
