# Micromouse2016 [![Build Status](https://travis-ci.org/ksemelka/Micromouse2016.svg?branch=master)](https://travis-ci.org/ksemelka/Micromouse2016)
Code that makes our Teensy 3.2 based robot be able to solve 16x16 mazes autonomously for the Micromouse competitions. 

Made with great effort by: Kyle Semelka and Chris Verdegan (IEEE-UCR)  
With thanks to: Andrew Nava and Emilio Barreiro

##Competitions
+ 3rd place at UCR Micromouse Competition (April 3rd)
+ 4th place at IEEE Region 6 Micromouse Competition at CSU Long Beach  (April 17)
+ 3rd place at UCLA All-America Micromouse Competition (May 1)
+ 4th place/Best Beginner at UCSD California Micromouse Competition (May 15)
  
##How It Works: Introduction
At the most basic, our "mouse" is really just a few motors being told how to rotate by a microcontroller. We make the motors turn forwards at the same rate, while correcting their movement using the information given to us by IR sensors. The sensors work by capturing the intensity of infrared light reflected back at the sensors from our LEDs emitting light at the walls of the maze. From this information, we can tell how far our mouse is from the walls to the front, left, and right, and we can use this correct our position. We can also tell if there is a wall or not in a certain direction. 

To solve the maze, we use a modified version of a "floodfill" algorithm. The start of the maze is always at one corner, and the end is always at the middle four spaces. We begin with a map of the maze without any walls. Then, we tell our mouse to move one cell at a time towards the middle, updating the walls of the maze along the way. It always tries to take the shortest path to the center, unless there is a wall in the way. By using this algorithm, the mouse is guaranteed to make it to the center.

##Parts List
+ 1 Perf Board (Through-hole board)
+ 1 Teensy 3.2
+ 7.4V LiPo Battery 
+ 3 IR LEDs
+ 3 IR Phototransistors
+ 2 Pololu HPCB Motors 150:1
+ 2 Pololu Wheels
+ 1 Motor Driver
+ 1 Voltage Regulator
+ 2 Pololu Hall Effect Quadrature Encoders
+ 1 Piezo Buzzer
+ 1 Bluetooth Module
+ Tears
+ All-nighters

###Destroyed Parts List (RIP)
+ 1 Teensy 3.2
+ 2 Motor drivers
+ 1 Voltage Regulator
+ 1 Pololu Encoder
+ 1 Pololu Motor
