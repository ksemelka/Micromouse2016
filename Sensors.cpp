#include "Sensors.h"
#include "LEDs.h"
#include <Arduino.h>

Sensors::Sensors(const byte leftPT, const byte frontPT, const byte rightPT)  {
  pinMode(leftPT, INPUT);        // Initialize phototransistors
  pinMode(frontPT, INPUT);
  pinMode(rightPT, INPUT);
}

void Sensors::view() {
  readSensors();
  printSmoothed();
}

int Sensors::calculateFrontSmoothed() {
      frontTotal -= frontReadings[frontIndex];
      frontReadings[frontIndex] = analogRead(frontPT);
      frontTotal += frontReadings[frontIndex];
      frontIndex++;
      if (frontIndex >= numReadings) {
        frontIndex = 0;
      }
      frontSmoothed = frontTotal / numReadings;
      return frontSmoothed;
    }
int Sensors::calculateLeftSmoothed() {
      leftTotal -= leftReadings[leftIndex];
      leftReadings[leftIndex] = analogRead(leftPT);
      leftTotal += leftReadings[leftIndex];
      leftIndex++;
      if (leftIndex >= numReadings) {
        leftIndex = 0;
      }
      leftSmoothed = leftTotal / numReadings;
      return leftSmoothed;
}
int Sensors::calculateRightSmoothed() {
      rightTotal -= rightReadings[rightIndex];
      rightReadings[rightIndex] = analogRead(rightPT);
      rightTotal += rightReadings[rightIndex];
      rightIndex++;
      if (rightIndex >= numReadings) {
        rightIndex = 0;
      }
      rightSmoothed = rightTotal / numReadings;
      return rightSmoothed;
}
void Sensors::readSensors() {
      for (int i = 0; i < numReadings; i++) {
        frontSmoothed = calculateFrontSmoothed();
        leftSmoothed = calculateLeftSmoothed();
        rightSmoothed = calculateRightSmoothed();
      }
      leftPTReading = analogRead(leftPT);
      frontPTReading = analogRead(frontPT);
      rightPTReading = analogRead(rightPT);
}

void Sensors::printPTReadings() const {
      Serial1.print("Left sensor: ");
      Serial1.print(leftPTReading);
      Serial1.print("\tFront sensor: ");
      Serial1.print(frontPTReading);
      Serial1.print("\tRight sensor: ");
      Serial1.println(rightPTReading);
}

void Sensors::printSmoothed() const {
      Serial1.print("Left sensor: ");
      Serial1.print(leftSmoothed);
      Serial1.print("\tFront sensor: ");
      Serial1.print(frontSmoothed);
      Serial1.print("\tRight sensor: ");
      Serial1.println(rightSmoothed);
}

int Sensors::getFrontSmoothed() const { return frontSmoothed; }
int Sensors::getLeftSmoothed() const { return leftSmoothed; }
int Sensors::getRightSmoothed() const { return rightSmoothed; }
unsigned int Sensors::getLeftPTReading() const { return leftPTReading; }
unsigned int Sensors::getFrontPTReading() const { return frontPTReading; }
unsigned int Sensors::getRightPTReading() const { return rightPTReading; }
