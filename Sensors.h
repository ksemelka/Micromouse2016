#ifndef SENSORS_H
#define SENSORS_H

const byte leftPT = A0;
const byte frontPT = A1;
const byte rightPT = A2;

class Sensors {
  public:
     Sensors(const byte leftPT, const byte frontPT, const byte rightPT) {
      pinMode(leftPT, INPUT);        // Initialize phototransistors
      pinMode(frontPT, INPUT);
      pinMode(rightPT, INPUT);
    }
    void view() {
      getPTReadings();
      printPTReadings();
    }
    void getPTReadings() {
      leftPTReading = analogRead(leftPT);
      frontPTReading = analogRead(frontPT);
      rightPTReading = analogRead(rightPT);
    }
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

    const int estimatedHighestValueLeft = 800;      // FIXME:10 These are wrong, fix wiring first
    const int estimatedHighestValueFront = 1030;   // The pin can't even read above 1023
    const int estimatedHighestValueRight = 200;
};

#endif  /*SENSORS_H*/
