#ifndef modulemainclass_h
#define modulemainclass_h
#include "Arduino.h"


class module {

public:
module();
 void begin(int *subfunc,int *pin, int *funcnum,int *functype);
 int getVal();
 void setVal(int16_t *value);
 void printSubfuncs(byte *subfunc,int functype);
 bool hasfunc();
 void refresh();
 int funcNum();
private:

protected:
    int _PIN;
    int _subfunc;
    int _funcnum;
    int _functype;
    int _lastState;
};
#endif
