#include "modulePotentiometer.h"
#include "Arduino.h"

int modPot::getVal(){
int16_t val= analogRead(module::_PIN);

    if (module::_subfunc==0){
        return val;
    }
    if (module::_subfunc==1){
        return val-1023;
    }
    if (module::_subfunc==2){
        return map(val,0,1023,0,8);
    }
    if (module::_subfunc==3){
        return map(val,0,1023,0,179);
    }
};
void modPot::setVal(int16_t value){

};

bool modPot::hasfunc(){
    return true;
}

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
}
