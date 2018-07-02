#include "moduleServo.h"
#include "Arduino.h"
#include <Servo.h>

Servo myservo;

modServ::modServ(){

}
void modServ::begin(int *pin){
    pinMode(pin, OUTPUT);
    myservo.attach(pin);
};
int modServ::getVal(){

};

void modServ::setVal(int16_t value,int *subfunc,int *pin,int *laststate){

myservo.write(value);

};



void modServ::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" 0-180" ));
};

}
