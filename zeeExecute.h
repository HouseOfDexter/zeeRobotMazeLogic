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

  void Execute(bool bypassWait = false);
  bool IsExecuting() { return _isExecuting; }
  zeeArduino* GetArduino() { return _arduino; }  
protected:
  virtual void AfterExecute();
  virtual void BeforeExecute();
  virtual void DoExecute(bool bypassWait) = 0;
  void SetIsExecuting(bool value) { _isExecuting = value; }
  unsigned long _lastUpdate = 0;
  zeeArduino* _arduino;
private:
  bool _isExecuting = false;
  unsigned long _executeLength = 0;
  unsigned long _runningLength = 0;
};

#endif