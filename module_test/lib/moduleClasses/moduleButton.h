#ifndef moduleButton_h
#define moduleButton_h
#include "Arduino.h"




class modBut {
public:
    modBut();
    virtual int getVal(int *subfunc,int *pin);
    virtual void printSubfuncs(byte subfunc);
    private:

    protected:


};
#endif
