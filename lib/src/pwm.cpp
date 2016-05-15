#include "../inc/pwm.h"
#include "../inc/Encoder.h"
#include "../inc/State.h"
#include "../inc/Sensors.h"
#include "../inc/Buzzer.h"
#include <cmath>
#include <Arduino.h>

extern Sensors sensors;
extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;
extern elapsedMillis wait;
extern byte nextState;

double accX = 160;
double accW = 1.5;
double decX = 350;
double decW = 1.5;
double curSpeedX = 0;
double curSpeedW = 0;
double targetSpeedX = 0;
double targetSpeedW = 0;
int posPwmX = 0;
int posPwmW = 0;
double posErrorX = 0;
double posErrorW = 0;
double oldPosErrorX = 0;
double oldPosErrorW = 0;
int leftBaseSpeed = 0;
int rightBaseSpeed = 0;
double encoderFeedbackX = 0;
double encoderFeedbackW = 0;
double sensorFeedback = 0;
double a_scale = 50;
bool useSensors = false;
double kpX = .4;
double kpW = 1;
double kdX = .1;
double kdW = 2;
volatile bool startingCell = false;
int moveSpeed = speed_to_counts(500*2);
int turnSpeed = speed_to_counts(500*2);
int returnSpeed = speed_to_counts(500*2);
int stopSpeed = speed_to_counts(100*2);
int maxSpeed = speed_to_counts(1400*2);

double speed_to_counts(double speed) {  // mm/s to counts/ms
  return speed / 2000.0 * 4.496;
}
double counts_to_speed(double counts) { // counts/20ms to mm/20s
  return counts * 2000.0 / 4.496;
}

void setLeftPwm(int speed) {
  if(speed > 255)//parameter check
    speed = 255;
  if(speed < -255)
    speed = -255;

    if(speed >= 0)//forward
    {
      analogWrite(LEFTlogic1, 0);
      analogWrite(LEFTlogic2, speed);
    }
    else//backward
    {
      analogWrite(LEFTlogic1, -speed);
      analogWrite(LEFTlogic2, 0);
    }
}
void setRightPwm(int speed) {
  if(speed > 255)
    speed = 255;
  if(speed < -255)
    speed = -255;

  if(speed >= 0)//forward
  {
    analogWrite(RIGHTlogic1, 0);
    analogWrite(RIGHTlogic2, speed);
  }
  else//backward
  {
    analogWrite(RIGHTlogic1, -speed);
    analogWrite(RIGHTlogic2, 0);
  }
}

void updateCurrentSpeed()
{
  if(curSpeedX < targetSpeedX)
  {
     curSpeedX += (double)speed_to_counts(accX*2);
    if(curSpeedX > targetSpeedX)
      curSpeedX = targetSpeedX;
  }
  else if(curSpeedX > targetSpeedX)
  {
     curSpeedX -= (double)speed_to_counts(decX*2);
    if(curSpeedX < targetSpeedX)
      curSpeedX = targetSpeedX;
  }
  if(curSpeedW < targetSpeedW)
  {
    curSpeedW += accW;
    if(curSpeedW > targetSpeedW)
      curSpeedW = targetSpeedW;
  }
  else if(curSpeedW > targetSpeedW)
  {
    curSpeedW -= decW;
    if(curSpeedW < targetSpeedW)
      curSpeedW = targetSpeedW;
  }
}

void calculateMotorPwm(void) // encoder PD controller
{
  int rotationalFeedback;

    /* simple PD loop to generate base speed for both motors */
  encoderFeedbackX = rightEncoderChange + leftEncoderChange;
  encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW
  if (useSensors) {
    sensorFeedback = sensorError/a_scale;//have sensor error properly scale to fit the system TODO
  }
  else {
    sensorFeedback = 0;
  }
  if (useSensors) {
    rotationalFeedback = encoderFeedbackW - sensorFeedback;
  }
  else {
    rotationalFeedback = encoderFeedbackW;
  }

  posErrorX += curSpeedX - encoderFeedbackX;
  posErrorW += curSpeedW - rotationalFeedback;

  posPwmX = kpX * posErrorX - kdX * (posErrorX - oldPosErrorX);
  posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);

  oldPosErrorX = posErrorX;
  oldPosErrorW = posErrorW;

  leftBaseSpeed = posPwmX - posPwmW;
  rightBaseSpeed = posPwmX + posPwmW;

  setLeftPwm(leftBaseSpeed);
  setRightPwm(rightBaseSpeed);
}

void moveOneCell() {
  targetSpeedW = 0;
  targetSpeedX = moveSpeed;

  do
  {
    /*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
    here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
    /*sample*/
    if(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed) < decX)
      targetSpeedX = maxSpeed;
    else
      targetSpeedX = moveSpeed;

    //there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
  }
  while( (encoderCount-oldEncoderCount) < ONECELLDISTANCE);
  //LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
  //LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
  //and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
  //these thresholds just in case the readings are too weak.

  oldEncoderCount = encoderCount; //update here for next movement to minimized the counts loss between cells.
}

int needToDecelerate(int dist, int curSpd, int endSpd)//speed are in encoder counts/ms, dist is in encoder counts
{
  if (curSpd<0) curSpd = -curSpd;
  if (endSpd<0) endSpd = -endSpd;
  if (dist<0) dist = 1;//-dist;
  if (dist == 0) dist = 1;  //prevent divide by 0

  return (abs(counts_to_speed((curSpd*curSpd - endSpd*endSpd)*100*(double)dist/4/2))); //dist_counts_to_mm(dist)/2);
  //calculate deceleration rate needed with input distance, input current speed and input targetspeed to determind if the deceleration is needed
  //use equation 2*a*S = Vt^2 - V0^2  ==>  a = (Vt^2-V0^2)/2/S
  //because the speed is the sum of left and right wheels(which means it's doubled), that's why there is a "/4" in equation since the square of 2 is 4
}

void resetSpeedProfile(void)
{
  //resetEverything;

  // //disable sensor data collecting functions running in 1ms interrupt
  useSensors = false;
 //   useGyro = false;
  // //no PID calculating, no motor lock
  // usePID = false;

  setLeftPwm(0);
  setRightPwm(0);

//  pidInputX = 0;
//  pidInputW = 0;
  curSpeedX = 0;
  curSpeedW = 0;
  targetSpeedX = 0;
  targetSpeedW = 0;
  posErrorX = 0;
  posErrorW = 0;
  oldPosErrorX = 0;
  oldPosErrorW = 0;
  leftEncoderOld = 0;
  rightEncoderOld = 0;
  leftEncoder = 0;
  rightEncoder = 0;
  leftEncoderCount = 0;
  rightEncoderCount = 0;
  encoderCount = 0;
  oldEncoderCount = 0;
  leftBaseSpeed = 0;
  rightBaseSpeed = 0;
 distanceLeftX = 0;
 distanceLeftW = 0;

  encoderValueLeft = 0;//reset left encoder count
  encoderValueRight = 0;//reset right encoder count
}


/********************************************************************
 *
 *    ooo        ooooo   .oooooo.   oooooo     oooo oooooooooooo
 *    `88.       .888'  d8P'  `Y8b   `888.     .8'  `888'     `8
 *     888b     d'888  888      888   `888.   .8'    888
 *     8 Y88. .P  888  888      888    `888. .8'     888oooo8
 *     8  `888'   888  888      888     `888.8'      888    "
 *     8    Y     888  `88b    d88'      `888'       888       o
 *    o8o        o888o  `Y8bood8P'        `8'       o888ooooood8
 *    ooo        ooooo oooooooooooo ooooo      ooo ooooooooooooo
 *    `88.       .888' `888'     `8 `888b.     `8' 8'   888   `8
 *     888b     d'888   888          8 `88b.    8       888
 *     8 Y88. .P  888   888oooo8     8   `88b.  8       888
 *     8  `888'   888   888    "     8     `88b.8       888
 *     8    Y     888   888       o  8       `888       888
 *    o8o        o888o o888ooooood8 o8o        `8      o888o
 *
 ********************************************************************
 */

void turnRightAndLeft() {
  useSensors = false;
  wait = 0;
  targetSpeedX = 0;
  targetSpeedW = 68;
  Serial.println("Entering While 1");
  while(1) {
    if (wait > 240) {
      wait -= 240;
      break;
    }
  }
  targetSpeedW = 0;
  Serial.println("Entering While 2");
  while (1) {
    if (wait > 1500) {
      wait -= 1500;
      break;
    }
  }
  targetSpeedW = -50;
  Serial.println("Entering While 3");
  while (1) {
    if (wait > 240) {
      wait -= 240;
      break;
    }
  }
  targetSpeedW = 0;
  Serial.println("Entering While 4");
  while (1) {
    if (wait > 1500) {
      wait -= 1500;
      break;
    }
  }
}

void turnLeftEncoderTicks() {
  resetSpeedProfile();
  distanceLeftW = TURNDISTANCELEFT;
  targetSpeedX = 0;
  targetSpeedW = 50;
  Serial.println("Entering While 1");
  while (distanceLeftW > TURNDISTANCELEFT - 1180) {
    if (wait > 10) {
      Serial.println(distanceLeftW);
      wait -= 10;
    }
  } // Stuck in loop until halfway
  targetSpeedW = 1;
  while (distanceLeftW > 0) {
    if (wait > 10) {
      Serial.println(distanceLeftW);
      wait -= 10;
    }
  } // Finish last half of turn
//  targetSpeedW = -1;
//  while (distanceLeftW < 0) {
//    if (wait > 10) {
//      Serial.println(distanceLeftW);
//      wait -= 10;
//    }
//  } // Finish last half of turn
  targetSpeedW = 0;
}

void turnRightEncoderTicks() {
  resetSpeedProfile();
  useSensors = false;
  turningRight = true;
  distanceLeftW = TURNDISTANCERIGHT;
  targetSpeedX = 0;
  targetSpeedW = -50;
  Serial.println("Entering While 1");
  while (distanceLeftW > TURNDISTANCERIGHT - 1300) {
    if (wait > 10) {
      Serial.println(distanceLeftW);
      wait -= 10;
    }
  } // Stuck in loop until about halfway
  targetSpeedW = -1;
  Serial.println("Entering While 2");
  while (distanceLeftW > 0) {   // Correct overshoot
    if (wait > 10) {
      Serial.println(distanceLeftW);
      wait -= 10;
    }
  }
//  targetSpeedW = 1;
//  while (distanceLeftW < 0) {
//    if (wait > 10) {
//      Serial.println(distanceLeftW);
//    }
//  }
  turningRight = false;
}

void goForwardAndBackward() {
  wait = 0;
  targetSpeedW = 0;
  targetSpeedX = 65;
//  Serial.println("Entering While 1");
  while(curSpeedX < 65) {
    if (wait > 1000) {
      wait -= 1000;
      break;
    }
  }
//  targetSpeedX = 0;
////  Serial.println("Entering While 2");
//  while (curSpeedX > 0) {
//    if (wait > 1000) {
//      wait -= 1000;
//      break;
//    }
//  }
  targetSpeedX = -65;
//  Serial.println("Entering While 3");
  while (curSpeedX > -65) {
    if (wait > 1000) {
      wait -= 1000;
      break;
    }
  }
//  targetSpeedX = 0;
//  Serial.println("Entering While 4");
//  while (curSpeedX < 0) {
//    if (wait > 1000) {
//      wait -= 1000;
//      break;
//    }
//  }
}

void goForwardDist(int dist) {
  useSensors = true;
  wait = 0;
  distanceLeftX += dist;
//  Serial1.println("B: ");
//  Serial1.println(distanceLeftX);
  if (startingCell) {
    distanceLeftX += 200;
    startingCell = false;
  }
  targetSpeedW = 0;
  while(distanceLeftX > 1000) {
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    playTone(1000, 10);
    targetSpeedX = GOODTARGETSPEEDX;
    if (wait > 50) {
      Serial1.println(distanceLeftX);
      wait -= 50;
    }
  }
  nextState = state();
  if (nextState != LEFT + RIGHT && nextState != RIGHT) {

  while(distanceLeftX > 800) {
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    playTone(500, 10);
    targetSpeedX = map(distanceLeftX, 0 , 1000,
                        0 , 30);
    if (sensors.frontPTReading > targetFront) {
      distanceLeftX = 0;
      break;
    }
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  while(distanceLeftX > 600) {
    targetSpeedX = map(distanceLeftX, 0 , 800,
                        0 , 20);
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    if (sensors.frontPTReading > targetFront) {
      distanceLeftX = 0;
      break;
    }
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  while(distanceLeftX > 400) {
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    targetSpeedX = map(distanceLeftX, 0 , 600,
                        0 , 15);
    if (sensors.frontPTReading > targetFront) {
      distanceLeftX = 0;
      break;
    }
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  while(distanceLeftX > 200) {
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    targetSpeedX = map(distanceLeftX, 0 , 400,
                        0 , 10);
    if (sensors.frontPTReading > targetFront) {
      distanceLeftX = 0;
      break;
    }
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  while(distanceLeftX > 0) {
    if (!(encoderValueRight % 100)) { // Veering correction
      encoderValueRight++;
    }
    targetSpeedX = map(distanceLeftX, 0 , 200,
                        1 , 5);
    if (sensors.frontPTReading > targetFront) {
      distanceLeftX = 0;
      break;
    }
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  targetSpeedX = -2;
  useSensors = false;
  while (distanceLeftX < 0) {
    if (wait > 20) {
      Serial1.println(distanceLeftX);
      wait -= 20;
    }
  }
  if (wallToTheFront() && sensors.frontPTReading < targetFront) {
    useSensors = true;
    elapsedMillis wait1;
    wait1 = 0;
    while (sensors.frontPTReading < targetFront) {
      if (wait > 20) {
        Serial1.println(distanceLeftX);
        wait -= 20;
      }
      targetSpeedX = 5;
      if (wait1 > 1000) {
        break;
      }
    }
    useSensors = false;
  }
  }
  else {
    while (distanceLeftX > 0) {
      if (!(encoderValueRight % 100)) { // Veering correction
        encoderValueRight++;
      }
      playTone(100, 5);
      targetSpeedX = GOODTARGETSPEEDX;
      if (wait > 20) {
        Serial1.println(distanceLeftX);
        wait -= 20;
      }
    }
  }
  useSensors = false;
}

void goBackwardDist(int dist) {
  useSensors = true;
  wait = 0;
  distanceLeftX = -dist;
  targetSpeedW = 0;
  while (distanceLeftX < 0) {
    targetSpeedX = map(distanceLeftX, -dist, 0,
                        -GOODTARGETSPEEDX, -10);
    if (wait > 20) {
      Serial.println(distanceLeftX);
      Serial.println(targetSpeedX);
      wait -= 20;
    }
  }
  targetSpeedX = 1;
  while (distanceLeftX > 0) {
    if (wait > 20) {
      Serial.println(distanceLeftX);
      wait -= 20;
    }
  }
  useSensors = false;
}
