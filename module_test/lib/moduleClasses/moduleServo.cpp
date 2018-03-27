#include "moduleServo.h"
#include "Arduino.h"
#include <Servo.h>

Servo myservo;

int modServ::getVal(){

};
void modServ::setVal(int16_t value){
myservo.write(value);
};

bool modServ::hasfunc(){
    return true;
}

void modServ::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" standard 0-180" ));};

}

void modServ::refresh(){

};
void modServ::begin(int subfunc,int pin, int funcnum){
  _PIN=pin;
  _subfunc=subfunc;
  _funcnum=funcnum;
  myservo.attach(pin);

}
