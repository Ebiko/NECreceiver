#include "NECreceiver.h"

/******************************** NEC *******************************/
unsigned long Nec_In(){

  unsigned int i=0;
  unsigned int j=0,
           count=0;
  unsigned long data_byte;
  unsigned int rusenieS,
           rusenie=0;               //datova premenna primane bity
  unsigned short pocet_bitov;

  data_byte = 0;
  pocet_bitov = 32;
  rusenieS = 255;
  
  for(i=0;i<rusenieS;i++){        //kontrola rusenia 74
    if(digitalRead(8)){
    return 9;
    }
  }
 delay(4);                     //čakanie na uplinutie start bitu
  i=0;
  while(1){
    if(i > 5000 && !digitalRead(8))   // 8 is one of the arduino pins
      break;
    if(i>6000)
      return 992;                     // the number 992 and the others is for debug, so I would know where the algorithm crashed.
    i++;
  }
  i=0;
  j=0;
  if(!digitalRead(8)){                      //cakanie na 1 po start bite
    while(1){
      if(digitalRead(8))
        break;
      if(j>1400){        //osetrenie chybneho bitu
        return 993;}
      j++;  
    }
  }else{
    return 994;
  }
  j=0;
  while(1){                          //cakanie na nulu prveho bitu
    count++;
    if(!digitalRead(8)){
      if(count>155){
        count = 0;
        if(j < 900)
          rusenie = 995;         // navrat REPEAT
        break;
      }else{
        return 996;
      }
    }
    if(j>1500)        //osetrenie chybneho bitu
      return 997;
    j++;
  }
  
  delayMicroseconds(450);
  j=0;
  i=0;
  while(pocet_bitov>0){     //kotrola poctu nacitanych bitov
    if(digitalRead(8)){              //čakanie na 1 po nule
      if(rusenie == 995)
        return 995;
      while(1){             //cakanie na nulu nasledujuceho bytu
        count++;            //počitanie trvania jednotky
        if(!digitalRead(8)){         // ci nastala nula
          if(count>300){     // predpokladana dlžka jednotky vacsia ako 60 - 70 impulzov
            data_byte = (data_byte << 1) + 1;           // zapis
            count = 0;
            break;
          }else{
            data_byte = (data_byte << 1) + 0;           //zapis
            count = 0;
            break;
          }
        }
        if(i>450)        //osetrenie chybneho bitu
          return 998;
        i++;
      }
      i=0;
      j=0;
      pocet_bitov--;
    }
    if(j>750)        //osetrenie chybneho bitu
      return 999;
    j++;
  }
  delayMicroseconds(560);
  return data_byte;
}
