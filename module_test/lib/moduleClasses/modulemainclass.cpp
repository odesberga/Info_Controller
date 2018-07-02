#include <modulemainclass.h>
#include "modulePotentiometer.h"
#include "moduleServo.h"
#include "moduleTempSens.h"
#include "moduleRelay.h"
#include "moduleButton.h"
module::module(){
};
void module::begin(int *subfunc,int *pin, int *funcnum,int *functype){
    _PIN=pin;
    _subfunc=subfunc;
    _funcnum=funcnum;
    _functype=functype;
    switch(_functype) {
        case 0:
            {
                pinMode(_PIN, INPUT);
            };
             break;
        case 1:
            {
                pinMode(_PIN, OUTPUT);
                digitalWrite(_PIN,HIGH);
            };
             break;
             case 3:
                 {
                     pinMode(_PIN, INPUT);
                    
                 };
                  break;
         case 4:
             {
                 pinMode(_PIN, OUTPUT);
                 digitalWrite(_PIN,HIGH);
             };
              break;
        break;
     }

};
void module::setVal(int16_t *value){

    switch(_functype) {

      case 2:
      {
          static modServ B;
          B.begin(_PIN);
          B.setVal(value,_subfunc,_PIN,_lastState);
        }
        break;
      case 4:
      {
        static modRel B;

          B.setVal(value,_subfunc,_PIN,_lastState);
        }
        break;
    }

_lastState=value;


};

void module::refresh(){

};
int module::getVal(){
    int val;
    switch(_functype) {
        case 0:
        {
            modPot B;
            val=B.getVal(_subfunc,_PIN);
        }
            break;
        case 1:
        {
            modBut B;
            val=B.getVal(_subfunc,_PIN);
        }
          break;
      case 2:
      {
          val=_lastState;
        }
        break;
        case 3:
        {
            modTempSens B;
            val=B.getVal(_subfunc,_PIN);
            }
          break;
      case 4:
      {
          modRel B;
          B.getVal(_subfunc,_PIN);
        }
        break;
    }

_lastState=val;
return val;

};
void module::printSubfuncs(byte *subfunc,int functype){
    switch(functype) {
        case 0:
        {
            modPot B;
            B.printSubfuncs(subfunc);
        }

         break;
        case 1:
        {
            modBut B;
        B.printSubfuncs(subfunc);
        }
          break;
          case 2:
{
              modServ B;
          B.printSubfuncs(subfunc);}

            break;
            case 3:

                { modTempSens B;
                 B.printSubfuncs(subfunc);}

              break;
          case 4:

             { modRel B;
           B.printSubfuncs(subfunc);}

            break;
    }

}
bool module::hasfunc(){
    return false;
}
int module::funcNum(){
return _funcnum;
};
