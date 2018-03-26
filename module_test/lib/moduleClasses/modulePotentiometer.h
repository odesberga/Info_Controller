#ifndef modulePotentiometer_h
#define modulePotentiometer_h
#include "Arduino.h"
#include <modulemainclass.h>



class modPot : public module {
public:

virtual int getVal();
virtual void setVal(int16_t value);
virtual bool hasfunc();
virtual void printSubfuncs(byte subfunc);
virtual void refresh();
private:

};
#endif
