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

//forward sensor  trigger pin needs to +1 of echo pin
const unsigned int  cTrigForwardPin = baseUS + 5;
const unsigned int cEchoForwardPin = baseUS + 4;

//right forward sensor trigger pin needs to +1 of echo pin
const unsigned int cTrigRFPin = baseUS + 3;
const unsigned int cEchoRFPin = baseUS + 2;

//right rear sensor trigger pin needs to +1 of echo pin
const unsigned int cTrigRRPin = baseUS + 1;
const unsigned int cEchoRRPin = baseUS + 0;

//LEDs to give us feedback
const unsigned int cLedPin1 = 3;
const unsigned int cLedPin2 = 2;
const unsigned int cLedPin3 = 1;

//LineReader
const unsigned int cLineReaderPin = 4;

const unsigned int cSonicSlop = 7;
const unsigned int cMeasureSamples = 10;
const unsigned int cSampleMeasurementDelay = 5;
const unsigned int cSonicOffset = 4;

const unsigned int cUpdateInterval = 10;
const unsigned int cLedUpdateInterval = 500;
const unsigned int cIntervalRunTime = 10;



#endif
