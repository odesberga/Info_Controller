#include "moduleTempSens.h"
#include "Arduino.h"
#include <OneWire.h>
#include <DallasTemperature.h>


int modTempSens::getVal(int *subfunc,int *pin){

  OneWire oneWire((int)pin);
  DallasTemperature Temp(&oneWire);
  Temp.requestTemperatures();
  return (int)Temp.getTempCByIndex(0);
};

void modTempSens::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" celsius" ));
};
}
