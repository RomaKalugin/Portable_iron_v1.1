#include "Buzzing.h"
#include "Setup_Pin.h"
#include "Arduino.h"

static unsigned long timing;
static const uint8_t interval_Buzz = 100;

void Buzzing(){
    timing = millis();
    if(timing < interval_Buzz){
      Pin_Buzz(1);
    }
    else 
    {
      Pin_Buzz(0);  
    }
}
