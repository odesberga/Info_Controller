#ifndef lcdHandler_h
#define lcdHandler_h
#include <Arduino.h>
#include <SensorHandler.h>

class lcdHandler
{

public:
    lcdHandler();
    void nextPage();
    void prevPage();
    void printToScreen(int sensidx);
    void begin();
    void refresh();
private:

};


#endif
