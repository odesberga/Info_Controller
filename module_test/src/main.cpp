#include <Arduino.h>
#include <Servo.h>
#include <ModuleCommonFunctions.h>
// #include <modulemainclass.h>
// #include "modulePotentiometer.h"

CommonFunctions CF;
//Servo myservo;
//module M[numberOfFunctions];
// new
// void * operator new (size_t size) { return malloc (size); }
// // placement new
// void * operator new (size_t size, void * ptr) { return ptr; }
// // delete
// void operator delete (void * ptr) { free (ptr); }

void setup() {
    Serial.begin(9600);
     while (!Serial) {};
      Serial.println();
     Serial.println("INIT");
CF.begin();
delay(200);
}

void loop() {
    // CF.RefreshFunctions();
    // delay(10);
    if(CF.gotData()){
        
          CF.ProcessFunctions(CF.func(),CF.setVal(),CF.Val());
    }
}
