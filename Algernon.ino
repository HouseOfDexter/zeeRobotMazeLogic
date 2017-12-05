#line 2 "Algernon.ino"
#include "Arduino.h"
#include "zeeArduino.h"
#include "zeeMotorPins.h"
#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeRobotMazeLogic.h"
#include "zeeLineReader.h"
#include "zeeSensorPins.h"
#include "zeeMotorPins.h"
#include "zeeMotors.h"
#include "zee298DualHBridgeMotorDriver.h"
#include "zeeDetection.h"
#include "zeeSonicSensors.h"

//default times in MS
const unsigned long cMoveTime = 50;

//distance in millimeters
const unsigned int cDistanceForwardDetection = 250;//in mm

//we use dependecy injection so we know when to free our memory
zeeArduino* arduino;
//we create another fascade for the leds because they update at a different interval
zeeArduino* ledarduino;
zeeArduino* nowait;
//unsigned int aleds[3] = { cLedPin1, cLedPin2, cLedPin3};
//zeeStateLED* leds = new zeeStateLED(ledarduino, aleds, 3);
zeeHC_SR04_Sensor* f_sr04;
zeeHC_SR04_Sensor* rf_sr04;
//we have an offset, on our robot the the sonic sensors are offset by about 5mm
zeeHC_SR04_Sensor* rr_sr04;
zeeSonicSensors* sonicSensors;
zeeLineReader* lineReader;
//we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots

zee298DualHBridgeMotorDriver* motors;
zeeDetector* detector;
zeeMoveRobot* moveRobot;

zeeRobotMazeLogic* mazeLogic;

void setup() {
  Serial.begin(9600);

  pinMode(13, OUTPUT);//onboard LED

  //we use dependecy injection so we know when to free our memory
  zeeArduino* arduino = new zeeArduino(cUpdateInterval, cIntervalRunTime);
  //we create another fascade for the leds because they update at a different interval
  zeeArduino* ledarduino = new zeeArduino(cLedUpdateInterval, cIntervalRunTime);
  zeeArduino* nowait = new zeeArduino(0, 0);
  //unsigned int aleds[3] = { cLedPin1, cLedPin2, cLedPin3};
  //zeeStateLED* leds = new zeeStateLED(ledarduino, aleds, 3);
  zeeHC_SR04_Sensor* f_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoForwardPin, cTrigForwardPin, cMeasureSamples, cSampleMeasurementDelay, cDistanceForwardDetection));
  zeeHC_SR04_Sensor* rf_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoRFPin, cTrigRFPin, cMeasureSamples, cSampleMeasurementDelay, 0));
  //we have an offset, on our robot the the sonic sensors are offset by about 5mm
  zeeHC_SR04_Sensor* rr_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoRRPin, cTrigRRPin, cMeasureSamples, cSampleMeasurementDelay, 0, cSonicOffset));
  zeeSonicSensors* sonicSensors = new zeeSonicSensors(nowait, 0, zeeSSParam(f_sr04, rf_sr04, rr_sr04, cSonicSlop, cDistanceForwardDetection));

  zeeLineReader* lineReader = new zeeLineReader(nowait, 0, cLineReaderLPin, cLineReaderMPin, cLineReaderRPin);

  //we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots
  //zeeDecoratorLed* ledDecorator = new zeeDecoratorLed(ledarduino, cMoveTime, NULL, leds);

  zee298DualHBridgeMotorDriver* motors = new zee298DualHBridgeMotorDriver(arduino, cMoveTime, zeeHBridgeMDparam(cMotorEnaPinA, cMotorIn1PinA, cMotorIn2PinA), zeeHBridgeMDparam(cMotorEnaPinB, cMotorIn1PinB, cMotorIn2PinB));

  zeeDetector* detector = new zeeDetector(nowait, sonicSensors, lineReader, cDistanceForwardDetection);

  zeeMoveRobot* moveRobot = zeeMotorFactory::SetMoveRobots(arduino, nowait, NULL, motors, detector, cMoveTime);

  //zeeRobotMazeLogic* mazeLogic = new zeeRobotMazeLogic(arduino, 0, moveRobot, detector);
  
  
  while (true)
  {
    unsigned int start = millis();
    detector->GetDetection();
    zeeDetection detection = zeeDetection(detector->DetectLine(), detector->ObstacleForward(), detector->IsEqual(), detector->DiffBetweenRightSensors());
    moveRobot->Handle(detection, false, false, 0);
    unsigned int stop = millis();
    Serial.print(stop - start);
    Serial.println(" total time");
  }

}

////delete leds;
//delete f_sr04;
//delete rf_sr04;
//delete rr_sr04;
//delete sonicSensors;
//delete lineReader;
//delete motors;
//delete moveRobot;
//delete mazeLogic;     
//delete detector;
//delete arduino;
//delete ledarduino;
//delete nowait;

void loop()
{

}

