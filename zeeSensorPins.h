#ifndef zeeSensorPins_h
#define zeeSensorPins_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/*
Note the echo pin should be +1 of the trigger pin if you use the zeeHC_SRO4 code.
The pins should line up with how you have your pins installed on the board.
*/

const unsigned int baseUS = 8;

//forward sensor  echo pin needs to +1 of trigger pin
const unsigned int echoForwardPin = baseUS + 5;
const unsigned int  trigForwardPin = baseUS + 4;

//right forward sensor echo pin needs to +1 of trigger pin
const unsigned int echoRFPin = baseUS + 3;
const unsigned int trigRFPin = baseUS + 2;

//right rear sensor echo pin needs to +1 of trigger pin
const unsigned int echoRRPin = baseUS + 1;
const unsigned int trigRRPin = baseUS + 0;

const unsigned int sonicSlop = 7;
const unsigned int MeasureSamples = 10;
const unsigned int SampleMeasurementDelay = 5;

#endif
