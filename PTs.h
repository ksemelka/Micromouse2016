// PT == PHOTOTRANSISTOR
#ifndef PTS_H
#define PTS_H

const byte leftPT = A0;
const byte middlePT = A1;
const byte rightPT = A2;

int leftPTReading;
int middlePTReading;
int rightPTReading;

const int estimatedHighestValueLeft = 800;      // FIXME:10 These are wrong, fix wiring first
const int estimatedHighestValueMiddle = 1030;   // The pin can't even read above 1023
const int estimatedHighestValueRight = 200;

int leftMappedValue;
int middleMappedValue;
int rightMappedValue;

void initializePTs() {
  pinMode(leftPT, INPUT);        // Initialize phototransistors
  pinMode(middlePT, INPUT);
  pinMode(rightPT, INPUT);
}

void getPTReadings() {
  leftPTReading = analogRead(leftPT);
  middlePTReading = analogRead(middlePT);
  rightPTReading = analogRead(rightPT);
}

void printPTReadings() {
  Serial.print("Left PT Reading: ");
  Serial.println(leftPTReading);
  Serial.print("Middle PT Reading: ");
  Serial.println(middlePTReading);
  Serial.print("Right PT Reading: ");
  Serial.println(rightPTReading);
}

void mapPTReadings() {
  leftMappedValue = map(leftPTReading, 0, estimatedHighestValueLeft, 0, 255);
  middleMappedValue = map(middlePTReading, 0, estimatedHighestValueMiddle, 0, 255);
  rightMappedValue = map(rightPTReading, 0, estimatedHighestValueRight, 0, 255);
}

void printMappedValues() {
  Serial.print("Left mapped value: ");
  Serial.println(leftMappedValue);
  Serial.print("Middle mapped value: ");
  Serial.println(middleMappedValue);
  Serial.print("Right mapped value: ");
  Serial.println(rightMappedValue);
}

#endif  /*PTS_H*/
