#ifndef zeeRobotMazeLogic_h
#define zeeRobotMazeLogic_h

#include "zeeArduino.h"
#include "zeeMoveRobot.h"
#include "zeeExecute.h"
#include "zeeDetection.h"




class zeeRobotMazeLogic : public zeeExecute
{
public:
  zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* moveRobot, zeeDetector* detector);
  virtual ~zeeRobotMazeLogic(); 
  
  bool IsFinished();
  
  unsigned int GetRobots();
protected:
  void AfterExecute() override;
  void DoExecute(bool bypassWait);
private:
  zeeMoveRobot* _moveRobot;
  zeeDetector* _detector;
  bool _isFinished = false;    
  unsigned int _robots = 0;
};

#endif

