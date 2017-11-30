#ifndef zeeExecute_h
#define zeeExecute_h
#include "zeeArduino.h"

class zeeExecute
{
  /*
    Abstract class that handles Execute, to make it easier to introduce decorator classes
  */
public:
  zeeExecute(zeeArduino* arduino, unsigned long executeLength = 0);
  virtual ~zeeExecute();

  void Execute();
  bool IsExecuting() { return _isExecuting; }
  zeeArduino* GetArduino() { return _arduino; }
protected:
  virtual void DoExecute() = 0;
  void SetIsExecuting(bool value) { _isExecuting = value; }  
  unsigned long _lastUpdate;
  zeeArduino* _arduino;
private:  
  bool _isExecuting;
  unsigned long _executeLength;
  unsigned long _runningLength;

};

#endif
