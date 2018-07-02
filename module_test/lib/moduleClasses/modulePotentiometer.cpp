#include "modulePotentiometer.h"
#include "Arduino.h"
int16_t lastval;

int modPot::getVal(int *subfunc,int *pin){
int16_t val= analogRead(pin);

    if (subfunc==0){
         return val;
    }
    if (subfunc==1){
        return val-1023;
    }
    if (subfunc==2){
        return map(val,0,1023,0,8);
    }
    if (subfunc==3){
        return map(val,0,1023,0,179);
    }
    if (subfunc==4){
        return (int)val * (5.0 / 1024.0);
    }
};


void modPot::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" standard " ));};
    if((all) || (subfunc==1)){
        if(all){Serial.print(F("1:" ));};
    Serial.print(F(" reverse " ));};
    if((all) || (subfunc==2)){
        if(all){Serial.print(F("2:" ));};
    Serial.print(F(" map to 8 " ));};
    if((all) || (subfunc==3)){
        if(all){Serial.print(F("3:" ));};
    Serial.print(F("map to 180 " ));};

if((all) || (subfunc==4)){
    if(all){Serial.print(F("4:" ));};
Serial.print(F("0 - 5 Volt " ));};
}
