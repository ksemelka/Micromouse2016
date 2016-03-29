#include "Motors.h"
#include "Sensors.h"
#include "LEDs.h"
#include "PID.h"
#include "Floodfill.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// Values for how far the mouse should be from walls
int targetFront;
int thresholdFront;
int targetSide;
int thresholdSide;

extern const byte encoderLEFT_A;
extern const byte encoderRIGHT_A;

volatile int RIGHT_PinALast = 0;
volatile int encoderValue = 0;

Motors motors;
Sensors sensors(leftPT, frontPT, rightPT);
void count(void); // code for counting the increasing values of encoder ticks

void setup() {
  Serial.begin(9600);
  delay(100);
  Serial.print("Starting...\n");
  attachInterrupt(4, count, FALLING);
  delay(1000);
}

void loop() {
  motors.turnRight();
  delay(1000);
  motors.turnLeft();
//  sensors.view();
}

void count() {
  encoderValue++;
}
void printEncoderValues() {
  Serial.print("Encoder Value: ");
  Serial.println(encoderValue);
}
