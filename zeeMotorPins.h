// zeeMotorPins.h

#ifndef _ZEEMOTORPINS_h
#define _ZEEMOTORPINS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

const int cMotorFL = 1;
const int cMotorFR = 2;
const int cMotorRL = 3;
const int cMotorRR = 4;

const int cMotorPinFL = -1;
const int cMotorPinFR = -1;
const int cMotorPinRL = -1;
const int cMotorPinRR = -1;

#endif
