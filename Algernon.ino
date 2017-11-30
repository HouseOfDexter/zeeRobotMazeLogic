#define ArduinoProg
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

//default times in MS
const unsigned int cDelay = 250;
const unsigned long cMoveTime = 100;

//distance in millimeters
const unsigned int cDistanceForwardDetection = 50;

void setup() {
  Serial.begin(9600);
}

void loop()
{
  //we use dependecy injection so we know when to free our memory
  zeeArduino* arduino = new zeeArduino(cUpdateInterval, cIntervalRunTime);
  //we create another fascade for the leds because they update at a different interval
  zeeArduino* ledarduino = new zeeArduino(cLedUpdateInterval, cIntervalRunTime);
  zeeArduino* nowait = new zeeArduino(0, 0);
  unsigned int aleds[3] = { cLedPin1, cLedPin2, cLedPin3};
  zeeStateLED* leds = new zeeStateLED(ledarduino, aleds, 3);
  zeeHC_SR04_Sensor* f_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoForwardPin, cTrigForwardPin,  cMeasureSamples, cSampleMeasurementDelay));
  zeeHC_SR04_Sensor* rf_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoRFPin, cTrigRFPin, cMeasureSamples, cSampleMeasurementDelay));
  //we have an offset, on our robot the the sonic sensors are offset by about 5mm
  zeeHC_SR04_Sensor* rr_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoRRPin, cTrigRRPin, cMeasureSamples, cSampleMeasurementDelay, cSonicOffset));
  zeeSonicSensors* sonicSensors = new zeeSonicSensors(nowait, 0, zeeSSParam(f_sr04, rf_sr04, rr_sr04, cSonicSlop, cDistanceForwardDetection));
  zeeLineReader* lineReader = new zeeLineReader(nowait, 0, cLineReaderRPin, cLineReaderMPin, cLineReaderLPin);
  //we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots
  zeeDecoratorLed* ledDecorator = new zeeDecoratorLed(ledarduino, cMoveTime, NULL, leds);
  zeeDecoratorPrintLn* printDecorator = new zeeDecoratorPrintLn(ledarduino, cMoveTime, ledDecorator);

  zee298DualHBridgeMotorDriver* motors = new zee298DualHBridgeMotorDriver(arduino, cMoveTime, zeeHBridgeMDparam(cMotorEnaPinA, cMotorIn1PinA, cMotorIn2PinA), zeeHBridgeMDparam(cMotorEnaPinB, cMotorIn1PinA, cMotorIn2PinB));
  zeeDetector* detector = new zeeDetector(nowait, sonicSensors, lineReader, cDistanceForwardDetection);
  zeeMoveRobot* moveRobot = zeeMotorFactory::SetMoveRobots(arduino, printDecorator, motors, detector, cMoveTime);
  
  zeeRobotMazeLogic* mazeLogic = new zeeRobotMazeLogic(arduino, cMoveTime, moveRobot, detector);
  
  //we sit in a loop until we are finished
  //note mazeLogic use the linereader to find the finish line
  while (!mazeLogic->IsFinished())
  {
    Serial.println("main loop");
    int loopcnt = 1;
    Serial.print(loopcnt++);
    Serial.print("");
    mazeLogic->Execute();
    mazeLogic->AfterExecute();
  }
  
  delete leds;
  delete f_sr04;
  delete rf_sr04;
  delete rr_sr04;
  delete sonicSensors;
  delete lineReader;
  delete motors;
  delete moveRobot;
  delete mazeLogic;     
  delete detector;
  delete arduino;
  delete ledarduino;
  delete nowait;
}

