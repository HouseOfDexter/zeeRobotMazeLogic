#ifndef zeeExecute_h
#define zeeExecute_h

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
  zeeExecute();
  ~zeeExecute();

  virtual void Execute() = 0;
};

#endif
