#ifndef SENSORS_H
#define SENSORS_H

const byte rightPT = A0;
const byte frontPT = A1;
const byte leftPT = A2;

class Sensors {
  public:
     Sensors(const byte leftPT, const byte frontPT, const byte rightPT) {
      pinMode(leftPT, INPUT);        // Initialize phototransistors
      pinMode(frontPT, INPUT);
      pinMode(rightPT, INPUT);
    }
    void view() {
      readSensors();
      printSmoothed();
    }
    int getFrontSmoothed() {
      frontTotal -= frontReadings[index];
      frontReadings[index] = analogRead(frontPT);
      frontTotal += frontReadings[index];
      frontIndex++;
      if (frontIndex >= numReadings) {
        frontIndex = 0;
      }
      frontSmoothed = frontTotal / numReadings;
      return frontSmoothed;
    }
    int getLeftSmoothed() {
      leftTotal -= frontReadings[index];
      leftReadings[index] = analogRead(frontPT);
      leftTotal += frontReadings[index];
      index++;
      if (index >= numReadings) {
        leftIndex = 0;
      }
      leftSmoothed = leftTotal / numReadings;
      return leftSmoothed;
    }
    int getRightSmoothed() {
      rightTotal -= rightReadings[index];
      rightReadings[index] = analogRead(rightPT);
      rightTotal += rightReadings[index];
      rightIndex++;
      if (rightIndex >= numReadings) {
        rightIndex = 0;
      }
      rightSmoothed = rightTotal / numReadings;
      return rightSmoothed;
    }
    void readSensors() {
      for (int i = 0; i < numReadings; i++) {
        frontSmoothed = getFrontSmoothed();
        leftSmoothed = getLeftSmoothed();
        rightSmoothed = getRightSmoothed();
      }
      leftPTReading = analogRead(leftPT);
      frontPTReading = analogRead(frontPT);
      rightPTReading = analogRead(rightPT);
    }
    unsigned int getLeftPTReading() const { return leftPTReading; }
    unsigned int getFrontPTReading() const { return frontPTReading; }
    unsigned int getRightPTReading() const { return rightPTReading; }

    void printPTReadings() const {
      Serial1.print("Left sensor: ");
      Serial1.print(leftPTReading);
      Serial1.print("\tFront sensor: ");
      Serial1.print(frontPTReading);
      Serial1.print("\tRight sensor: ");
      Serial1.println(rightPTReading);
    }
    void printSmoothed() const {
      Serial1.print("Left sensor: ");
      Serial1.print(leftSmoothed);
      Serial1.print("\tFront sensor: ");
      Serial1.print(frontSmoothed);
      Serial1.print("\tRight sensor: ");
      Serial1.println(rightSmoothed);
    }
  private:
    unsigned int leftPTReading;
    unsigned int frontPTReading;
    unsigned int rightPTReading;

    int leftMappedValue;
    int frontMappedValue;
    int rightMappedValue;

    const int estimatedHighestValueLeft = 950;
    const int estimatedHighestValueFront = 970;
    const int estimatedHighestValueRight = 970;

    static const byte numReadings = 10;

    int frontTotal;
    int leftTotal;
    int rightTotal;

    byte frontIndex;
    byte leftIndex;
    byte rightIndex;

    int frontReadings[numReadings];
    int leftReadings[numReadings];
    int rightReadings[numReadings];

    int frontSmoothed;
    int leftSmoothed;
    int rightSmoothed;

};

#endif  /*SENSORS_H*/
