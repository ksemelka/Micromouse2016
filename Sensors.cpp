#include "Sensors.h"
#include "LEDs.h"
#include "State.h"
#include <Arduino.h>

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
