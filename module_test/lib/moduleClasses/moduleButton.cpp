#include "moduleButton.h"
#include "Arduino.h"

modBut::modBut(){};
int modBut::getVal(int *subfunc,int *pin){
int val= digitalRead(pin);

    if (subfunc==0){
        if(val==0){
        val=100;
    } else {
        val=0;
    };
    }
    if (subfunc==1){
        if(val==1){val= 100;} else{val=0;};
    }
    return val;
};
void modBut::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" 1=on 0=off" ));};
    if((all) || (subfunc==1)){
        if(all){Serial.print(F("1:" ));};
    Serial.print(F(" 0=on 1=off " ));};

};
