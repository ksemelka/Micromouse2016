#include "../inc/Sensors.h"
#include "../inc/LEDs.h"
#include "../inc/State.h"
#include "../inc/pwm.h"
#include <Arduino.h>

double sensorError;
extern Sensors sensors;

void calculateSensorError() {
  if (wallToTheRight() && wallToTheLeft()) {
    sensorError = sensors.rightPTReading - sensors.leftPTReading;
  }
  else if (wallToTheRight() && !wallToTheLeft()) {
    sensorError = sensors.rightPTReading - targetRight;
  }
  else if (wallToTheLeft() && !wallToTheRight()) {
    sensorError = targetLeft - sensors.leftPTReading;
  }
  else if (!wallToTheLeft() && !wallToTheRight()) {
    sensorError = 0;
  }
}

Sensors::Sensors(const byte leftPT, const byte frontPT, const byte rightPT)  {
  pinMode(leftPT, INPUT);        // Initialize phototransistors
  pinMode(frontPT, INPUT);
  pinMode(rightPT, INPUT);
}

void Sensors::printReadings() const {
      Serial1.print("Left sensor: ");
      Serial1.print(leftPTReading);
      Serial1.print("\tFront sensor: ");
      Serial1.print(frontPTReading);
      Serial1.print("\tRight sensor: ");
      Serial1.println(rightPTReading);
}
