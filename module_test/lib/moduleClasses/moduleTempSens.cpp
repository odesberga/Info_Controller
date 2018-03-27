#include "moduleTempSens.h"
#include "Arduino.h"
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "Wire.h"
#define I2C_ADDR 0x3f



int modTempSens::getVal(){

  OneWire oneWire(_PIN);
  DallasTemperature Temp(&oneWire);

  Temp.requestTemperatures();
  return (int)Temp.getTempCByIndex(0);


};
void modTempSens::setVal(int16_t value){

};

bool modTempSens::hasfunc(){
    return true;
}

void modTempSens::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" standard 0-180" ));};

}

void modTempSens::refresh(){

};
void modTempSens::begin(int subfunc,int pin, int funcnum){
  _PIN=pin;
  _subfunc=subfunc;
  _funcnum=funcnum;


}
