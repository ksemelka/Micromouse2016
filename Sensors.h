#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

const byte rightPT = A0;
const byte frontPT = A1;
const byte leftPT = A2;

class Sensors {
  public:
     Sensors(const byte leftPT, const byte frontPT, const byte rightPT);
    void view();
    int calculateFrontSmoothed();
    int calculateLeftSmoothed();
    int calculateRightSmoothed();
    void readSensors();
    int getFrontSmoothed() const;
    int getLeftSmoothed() const;
    int getRightSmoothed() const;
    unsigned int getLeftPTReading() const;
    unsigned int getFrontPTReading() const;
    unsigned int getRightPTReading() const;

    void printPTReadings() const;
    void printSmoothed() const;
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
