#ifndef zeeRobotMazeLogic_h
#define zeeRobotMazeLogic_h

#include "zeeMoveRobot.h"
#include "zeeExecute.h"
#include "zeeDetection.h"

class zeeRobotMazeLogic : public zeeExecute
{
public:
  zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* moveRobot, zeeDetector* detector);
  virtual ~zeeRobotMazeLogic(); 

  void AfterExecute();

  bool IsFinished();
protected:
  void DoExecute();
private:
  zeeMoveRobot* _moveRobot;
  zeeDetector* _detector;
  bool _isFinished = false;  
};

#endif