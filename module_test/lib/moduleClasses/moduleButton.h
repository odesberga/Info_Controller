#ifndef moduleButton_h
#define moduleButton_h
#include "Arduino.h"
#include <modulemainclass.h>



class modBut : public module {
public:

virtual int getVal();
virtual void setVal(int16_t value);
virtual bool hasfunc();
virtual void printSubfuncs(byte subfunc);
virtual void refresh();
private:

};
#endif
