#include "Arduino.h"
#include "VibroSens.h"
#include "BUZZING.h"

static bool state_vibro_sens = false;
static const uint8_t ADC1 = A1;
static uint16_t ADC1_val;
static uint16_t filtered_val;
static uint8_t num_read;

unsigned long time_on = 0;
unsigned long timer = 0;

void Tracking_vibro(){
  ADC1_val = 0;
  for(num_read= 0; num_read < 10; num_read++){
  ADC1_val += analogRead(ADC1);
  //delay(10);
  }
  filtered_val = ADC1_val / num_read;
  

  if(filtered_val > 500){
    state_vibro_sens = false;
    timer = 0;
  }
  else if(filtered_val < 500){
    timer++;
    if(timer > 500){
    state_vibro_sens = true;
    timer = 0;
    }
  }
}

bool GetVibroState(){
  return state_vibro_sens;
}