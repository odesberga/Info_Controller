#include <modulesmsclass.h>



smsclass::smsclass(){


};
void smsclass::begin(int subfunc,int pin, int funcnum){
_PIN=pin;
_subfunc=subfunc;
_funcnum=funcnum;
};
void smsclass::setVal(int16_t value){

};
void smsclass::refresh(){

};
int smsclass::getVal(){
return 1;
};
void smsclass::printSubfuncs(byte subfunc){

}
bool smsclass::hasfunc(){
    return false;
}
int smsclass::funcNum(){
    return _funcnum;
};
