#ifndef SENSORS_H
#define SENSORS_H
#include <Arduino.h>

const byte rightPT = A0;
const byte frontPT = A1;
const byte leftPT = A2;

extern double sensorError;
void calculateSensorError();

class Sensors {
  public:
    Sensors(const byte leftPT, const byte frontPT, const byte rightPT);
    void printReadings() const;
    void turnSensorsOn();
    void turnSensorsOff();

    int leftPTReading;
    int frontPTReading;
    int rightPTReading;
};

#endif  /*SENSORS_H*/
