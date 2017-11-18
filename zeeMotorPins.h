#ifndef zeeMotorPins_h
#define zeeMotorPins_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

const int cMotorFL = 1;
const int cMotorFR = 2;
const int cMotorRL = 3;
const int cMotorRR = 4;

//L298 Dual Bridge
const int cMotorEnaPinA = 2;
const int cMotorIn1PinA = 1;
const int cMotorIn2PinA = 0;

const int cMotorEnaPinB = 7;
const int cMotorIn1PinB = 6;
const int cMotorIn2PinB = 5;

#endif
