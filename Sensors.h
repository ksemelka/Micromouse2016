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
      printPTReadings();
    }
    void readSensors() {
      leftPTReading = analogRead(leftPT);
      frontPTReading = analogRead(frontPT);
      rightPTReading = analogRead(rightPT);
    }
    unsigned int getLeftPTReading() const { return leftPTReading; }
    unsigned int getFrontPTReading() const { return frontPTReading; }
    unsigned int getRightPTReading() const { return rightPTReading; }

    void printPTReadings() const {
      Serial.print("Left sensor: ");
      Serial.print(leftPTReading);
      Serial.print("\tFront sensor: ");
      Serial.print(frontPTReading);
      Serial.print("\tRight sensor: ");
      Serial.println(rightPTReading);
    }
    void mapPTReadings() {
      leftMappedValue = map(leftPTReading, 0, estimatedHighestValueLeft, 0, 255);
      frontMappedValue = map(frontPTReading, 0, estimatedHighestValueFront, 0, 255);
      rightMappedValue = map(rightPTReading, 0, estimatedHighestValueRight, 0, 255);
    }
    void printMappedValues() const {
      Serial.print("Left mapped value: ");
      Serial.print(leftMappedValue);
      Serial.print("\tFront mapped value: ");
      Serial.print(frontMappedValue);
      Serial.print("\tRight mapped value: ");
      Serial.println(rightMappedValue);
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
};

#endif  /*SENSORS_H*/
