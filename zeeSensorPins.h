#ifndef zeeSensorPins_h
#define zeeSensorPins_h

const unsigned int cEchoRFPin = 24;
const unsigned int cTrigRFPin = 26;
const unsigned int cEchoRRPin = 28;
const unsigned int cTrigRRPin = 30;
const unsigned int  cEchoForwardPin = 34;
const unsigned int  cTrigForwardPin = 32;

//LineReader
const unsigned int cLineReaderRPin = 10;
const unsigned int cLineReaderMPin = 4;
const unsigned int cLineReaderLPin = 2;

const unsigned int cSonicSlop = 7;
const unsigned int cMeasureSamples = 1;

//this delay is in micrseconds
const unsigned int cSampleMeasurementDelay = 5;
const unsigned int cSonicOffset = 4;

const unsigned int cUpdateInterval = 100;
const unsigned int cLedUpdateInterval = 500;
const unsigned int cIntervalRunTime = 100;


#endif

