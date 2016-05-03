#include "../inc/Buzzer.h"

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
 // for(uint16_t i=320; i>280; i--)
   //  playTone(i,9);

playTone(800, 40);
playTone(700, 30);
playTone(600, 40);
playTone(650, 50);
playTone(750, 20);
delay(100);
playTone(600, 40);
playTone(400, 20);
playTone(300, 60);
playTone(200, 80);
}

void bootTone() {
playTone(1000, 50);
playTone(2000, 40);
playTone(1000, 50);
//
////delay(100);
//
//playTone(1500, 20);
//playTone(2500, 20);
//playTone(1500, 20);
//
////delay(100);
//
//playTone(800, 20);
//playTone(900, 20);
//playTone(6000, 20);
//
////delay(100);
//
//playTone(900, 20);
//playTone(1000, 20);
//playTone(1300, 20);

}


void startTone(){
  playTone(900, 100);
  delay(30);
  playTone(1000, 100);

}

void frontWallTone(){
  playTone(200, 300);
}
