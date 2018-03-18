#ifndef SensorHandler_h
#define SensorHandler_h
#include <Arduino.h>
#include <stdint.h>
#include <SD.h>
#define byte uint8_t
#define NameLength 10
#define SensorMaxCount 100
#define EEslotlength NameLength + 20
#define EEslotTotallength NameLength + 20 *SensorMaxCount

struct SensorData {
    char SensorName[NameLength];
    byte SensorAddress=0;
    byte SensorFunction=0;
    int16_t SensorThreshold=0;
    char ThresholdPosNeg=0;
    char Alarmlevel=0;
    char PrintToScreen=0;
    byte ForwardSensorAddress=0;
    byte ForwardSensorFunction=0;
    int16_t LastValue=0;
};


class SensorHandler
{

  public:
    SensorHandler(int count);
    int sensorCount();
    void clearEEPROM(int slot);
    void addFromEEPROM();
    bool delFromEEPROM(char *sensorName);
    bool saveToEEPROM(char *SensorStr,int len);
    void getStringFromEEPROM(int slot, String &retstring);
    void add(char * SensorStr);
    SensorData getSensor(uint8_t Address,uint8_t Function);
    int SensorCount=0;
     SensorData _SensorData[SensorMaxCount];

     bool savetosd(char* filename);
     bool loadfromsd(char* filename);
  private:


};






#endif
