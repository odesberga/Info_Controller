#include "moduleButton.h"
#include "Arduino.h"
long lastDebounceTime = 0;
long debounceDelay = 50;
int buttonState;
bool outstate;
int lastButtonState = LOW;
int modBut::getVal(){
     pinMode(module::_PIN, INPUT);
int16_t val= digitalRead(module::_PIN);

    if (module::_subfunc==0){

    }
    if (module::_subfunc==1){
        if(val==1){val= 0;} else{val=1;};

    }
    if (module::_subfunc==2){
    val= outstate;
    }
    return val;
};
void modBut::setVal(int16_t value){

};

bool modBut::hasfunc(){
    return true;
}

void modBut::printSubfuncs(byte subfunc){
    bool all=false;
    if(subfunc > 4){all=true;};
    if((all) || (subfunc==0)){
        if(all){Serial.print(F("0:" ));};
    Serial.print(F(" standard " ));};
    if((all) || (subfunc==1)){
        if(all){Serial.print(F("1:" ));};
    Serial.print(F(" invert " ));};
    if((all) || (subfunc==2)){
        if(all){Serial.print(F("2:" ));};
    Serial.print(F(" toggle " ));};
}

void modBut::refresh(){
 pinMode(module::_PIN, INPUT);
    int reading = digitalRead(module::_PIN);
    if (reading != lastButtonState) {
      lastDebounceTime = millis();
  };

    if ((millis() - lastDebounceTime) > debounceDelay) {
      if (reading != buttonState) {
        buttonState = reading;

        if (buttonState == HIGH) {
          outstate = !outstate;
        }
      }
  };


    lastButtonState = reading;
};
