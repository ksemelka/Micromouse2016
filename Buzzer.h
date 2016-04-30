#ifndef BUZZER_H
#define BUZZER_H
#define BUZZER   20
#include "Arduino.h"

void initializeBuzzer();

// play tone on a piezo BUZZER: tone shorter values produce higher frequencies
//  which is opposite beep() but avoids some math delay - similar to code by Erin Robotgrrl

void playTone(uint16_t tone1, uint16_t duration);

// another sound producing function similar to http://web.media.mit.edu/~leah/LilyPad/07_sound_code.html
void beep (int16_t frequencyInHertz, long timeInMilliseconds);

void chirp();

void bootTone();

void startTone();

void frontWallTone();

#endif /*BUZZER_H*/
