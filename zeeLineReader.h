#ifndef zeeLineReader_h
#define zeeLineReader_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class zeeLineReader
{
public:
  zeeLineReader();
  ~zeeLineReader();

  bool DetectLine();
};

#endif
