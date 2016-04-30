#include "Buzzer.h"

void initializeBuzzer() {
  pinMode(BUZZER, OUTPUT);
}

// play tone on a piezo BUZZER: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl

void playTone(uint16_t tone1, uint16_t duration) {
  if(tone1 < 50 || tone1 > 15000) return;  // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
     digitalWrite(BUZZER, HIGH);
     delayMicroseconds(tone1);
     digitalWrite(BUZZER, LOW);
     delayMicroseconds(tone1);
  }
}

// another sound producing function similar to http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
void beep (int16_t frequencyInHertz, long timeInMilliseconds) {
    long x;
    long delayAmount = (long)(1000000/frequencyInHertz);
    long loopTime = (long)((timeInMilliseconds*1000)/(delayAmount*2));
    for (x=0;x<loopTime;x++) {
       digitalWrite(BUZZER,HIGH);
       delayMicroseconds(delayAmount);
       digitalWrite(BUZZER,LOW);
       delayMicroseconds(delayAmount);
    }
}

void chirp() {  // Bird chirp
  for(uint16_t i=320; i>280; i--)
     playTone(i,9);
}

void bootTone() {
  playTone(527, 250);
  //delay(20);
  playTone(470, 250);
  //delay(20);
  playTone(419, 250);
  //delay(20);
  playTone(395, 250);
  //delay(20);
  playTone(352, 250);
  //delay(20);
  playTone(313, 250);
  //delay(20);
  playTone(279, 250);
  //delay(20);
  playTone(263, 250);
}


void startTone(){
  playTone(1000, 500);
  delay(100);
  playTone(1000, 500);
  delay(100);
  playTone(1000, 500);
  delay(100);
  playTone(500, 1200);
}

void frontWallTone(){
  playTone(200, 300);
}
