#include "Buzzing.h"
#include "Setup_Pin.h"
#include "Arduino.h"

static uint8_t buzz = 0;

void Buzzing(){
    if (buzz == 0){
      buzz = 1;
    }
    else {
      buzz = 0;
    }
    switch(buzz){
      case 0: Pin_Buzz(0); break;
      case 1: Pin_Buzz(1); break;
    }
}
