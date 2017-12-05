#ifndef zeeLineReader_h
#define zeeLineReader_h
#include "zeeArduino.h"
#include "zeeExecute.h"

class zeeLineReader: public zeeExecute
{
public:
  zeeLineReader(zeeArduino* arduino, unsigned long executeLength, unsigned int lPin, unsigned int mPin, unsigned int rPin);
  virtual ~zeeLineReader();

  bool DetectRight();
  bool DetectLeft();
  bool DetectMiddle();
protected:
  void DoExecute(bool bypassWait);
private:
  zeeArduino* arduino;
  unsigned int _rPin = 0;
  unsigned int _mPin = 0;
  unsigned int _lPin = 0;
  
  bool _detectRight = false;
  bool _detectLeft = false;
  bool _detectMiddle = false;
};

#endif

