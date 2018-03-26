#ifndef modulemainclass_h
#define modulemainclass_h
#include "Arduino.h"


class module {

public:
module();
void begin(int subfunc,int pin, int funcnum);
virtual int getVal();
virtual void setVal(int16_t value);
virtual void printSubfuncs(byte subfunc);
virtual bool hasfunc();
virtual void refresh();
int funcNum();
private:

protected:
    int _PIN;
    int _subfunc;
    int _funcnum;

};
#endif
