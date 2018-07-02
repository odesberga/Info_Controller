#include "moduleRelay.h"
#include "Arduino.h"

bool s=false;
int modRel::getVal(int *subfunc,int *pin){

return digitalRead(pin);
};
void modRel::setVal(int16_t value,int *subfunc,int *pin,int *laststate){
if (subfunc==0){
        if(value > 0){
          digitalWrite(pin,0);
        } else {
          digitalWrite(pin,1);
        }
      }
    if (subfunc==1){
        if(value >= 1){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
      if (subfunc==2){
        if(value >= 2){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
      if (subfunc==3){
        if(value >= 3){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
     if (subfunc==4){
        if(value >= 4){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
     if (subfunc==5){
        if(value >= 5){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
      if (subfunc==6){
        if(value >= 6){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
      if (subfunc==7){
        if(value >= 7){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }
      if (subfunc==8){
        if(value >= 8){
            digitalWrite(pin,0);
          } else {
            digitalWrite(pin,1);
          }
      }

      if (subfunc==9){
        if(value >0){
            s=!s;
            digitalWrite(pin,s);
          }
      }


};

void modRel::printSubfuncs(byte subfunc){
//     bool all=false;
//     if(subfunc > 99){all=true;};
//     if((all) || (subfunc==0)){
//         if(all){Serial.print(F("0:" ));};
//     Serial.print(F(" 0 off, > 0 on" ));};
// if(all){Serial.println();};
//     if((all) || (subfunc==1)){
//       if(all){Serial.print(F("1:" ));};
//     Serial.print(F("  >= 1 on < 1 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==2)){
//       if(all){Serial.print(F("2:" ));};
//     Serial.print(F("  >= 2 on < 2 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==3)){
//     if(all){Serial.print(F("3:" ));};
//     Serial.print(F("  >= 3 on < 3 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==4)){
//     if(all){Serial.print(F("4:" ));};
//     Serial.print(F("  >= 4 on < 4 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==5)){
//     if(all){Serial.print(F("5:" ));};
//     Serial.print(F("  >= 5 on < 5 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==6)){
//     if(all){Serial.print(F("6:" ));};
//     Serial.print(F("  >= 6 on < 6 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==7)){
//     if(all){Serial.print(F("7:" ));};
//     Serial.print(F("  >= 7 on < 7 off" ));};
//  if(all){Serial.println();};
//     if((all) || (subfunc==8)){
//     if(all){Serial.print(F("8:" ));};
//     Serial.print(F("  >= 8 on < 8 off" ));};
//  if(all){Serial.println();};
//  if((all) || (subfunc==9)){
//  if(all){Serial.print(F("9:" ));};
//  Serial.print(F("  >0 toggle" ));};
// if(all){Serial.println();};
}
