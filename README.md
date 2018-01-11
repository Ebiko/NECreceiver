# NECreceiver
NEC IR Protocol

Arduino/UNO version of NEC receiving protocol

Comments temporarily in Slovak language.

Implementation

the header and source file are stored in folder named NECreceiver which is located among the other arduino libraries.

/********* File.INO *********/
extern "C" {
#include "NECreceiver.h"
};

int RECV_PIN = 8;
void loop() {
  if (!digitalRead(8)) {
    unsigned long decCode = Nec_In();
    
    /* I got the number 16754775 from printing the decCode variable.
     * On my remote controller it is a plus sign
     */
     
    if(decCode == 16754775){
      // some code
    }
  }
}
/******* end.INO ***********/
