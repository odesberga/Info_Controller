#include "moduleRelay.h"
#include "Arduino.h"


int modRel::getVal(){




};
void modRel::setVal(int16_t value){
switch (_subfunc){
      case 0:{
        if(value > 0){
          digitalWrite(_PIN,1);
        } else {
          digitalWrite(_PIN,0);
        }
      }
      break;
      case 1:{
        if(value >= 1){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 2:{
        if(value >= 2){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 3:{
        if(value >= 3){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 4:{
        if(value >= 4){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 5:{
        if(value >= 5){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 6:{
        if(value >= 6){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;

      case 7:{
        if(value >= 7){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
      case 8:{
        if(value >= 8){
            digitalWrite(_PIN,1);
          } else {
            digitalWrite(_PIN,0);
          }
      }
      break;
}
};

bool modRel::hasfunc(){
    return true;
}

void modRel::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 99){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" standard 0 off > 0 on" ));};

    if((all) || (subfunc==1)){
      if(all){Serial.print(F("1:" ));};
    Serial.print(F("  >= 1 on < 1 off" ));};

    if((all) || (subfunc==2)){
      if(all){Serial.print(F("2:" ));};
    Serial.print(F("  >= 2 on < 2 off" ));};

    if((all) || (subfunc==3)){
    if(all){Serial.print(F("3:" ));};
    Serial.print(F("  >= 3 on < 3 off" ));};

    if((all) || (subfunc==4)){
    if(all){Serial.print(F("4:" ));};
    Serial.print(F("  >= 4 on < 4 off" ));};

    if((all) || (subfunc==5)){
    if(all){Serial.print(F("5:" ));};
    Serial.print(F("  >= 5 on < 5 off" ));};

    if((all) || (subfunc==6)){
    if(all){Serial.print(F("6:" ));};
    Serial.print(F("  >= 6 on < 6 off" ));};

    if((all) || (subfunc==7)){
    if(all){Serial.print(F("7:" ));};
    Serial.print(F("  >= 7 on < 7 off" ));};

    if((all) || (subfunc==8)){
    if(all){Serial.print(F("8:" ));};
    Serial.print(F("  >= 8 on < 8 off" ));};
}

void modRel::refresh(){

};

void modRel::begin(int subfunc,int pin, int funcnum){
  _PIN=pin;
  _subfunc=subfunc;
  _funcnum=funcnum;
  pinMode(_PIN, OUTPUT);
}
