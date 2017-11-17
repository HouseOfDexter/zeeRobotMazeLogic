#ifndef zeeExecute_h
#define zeeExecute_h
#include "zeeArduino.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
class zeeExecute
{
  /*
    Abstract class that handles Execute, to make it easier to introduce decorator classes
  */
public:
  zeeExecute(zeeArduino* arduino, unsigned long executeLength = 0);
  ~zeeExecute();

  void Execute();
  bool IsExecuting() { return _isExecuting; }
protected:
  virtual void DoExecute() = 0;
  void SetIsExecuting(bool value) { _isExecuting = value; }  
  unsigned long _lastUpdate;
private:
  zeeArduino* _arduino;
  bool _isExecuting;
  unsigned long _executeLength;
  unsigned long _runningLength;

};

#endif
