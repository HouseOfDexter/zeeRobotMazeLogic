#ifndef zeeSensorPins_h
#define zeeSensorPins_h

const unsigned int baseUS = 8;

const unsigned int cTrigRFPin = baseUS + 3;//11
const unsigned int cEchoRFPin = baseUS + 2;//10

const unsigned int cTrigRRPin = baseUS + 1;//9
const unsigned int cEchoRRPin = baseUS + 0;//8

const unsigned int  cTrigForwardPin = 5;
const unsigned int cEchoForwardPin = 4;


//LEDs to give us feedback
const unsigned int cLedPin1 = 3;
const unsigned int cLedPin2 = 2;
const unsigned int cLedPin3 = 1;

//LineReader
const unsigned int cLineReaderRPin = 10;
const unsigned int cLineReaderMPin = 4;
const unsigned int cLineReaderLPin = 2;

const unsigned int cSonicSlop = 7;
const unsigned int cMeasureSamples = 10;
const unsigned int cSampleMeasurementDelay = 5;
const unsigned int cSonicOffset = 4;

const unsigned int cUpdateInterval = 10;
const unsigned int cLedUpdateInterval = 500;
const unsigned int cIntervalRunTime = 10;



#endif

