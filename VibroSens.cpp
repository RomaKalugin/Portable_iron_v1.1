#include "Arduino.h"
#include "VibroSens.h"
#include "Buzzing.h"
#include "Switch_Menu.h"

static bool state_vibro_sens = 1;
static uint8_t state_vibro_current = 0;
static uint8_t vibro_state_previous = 0;
static const uint8_t ADC1 = A1;
static uint16_t ADC1_val;
static uint16_t filtered_val;
static uint8_t num_read;

unsigned long time_on = 0;
unsigned long timer = 0;

void Tracking_vibro(){
  //ADC1_val = 0;
  //for(num_read= 0; num_read < 10; num_read++){
  ADC1_val = analogRead(ADC1);
  //}
  //filtered_val = ADC1_val / num_read;
  
  if(ADC1_val > 501){
    state_vibro_current = 1;
  }
  else if(ADC1_val < 500){
    state_vibro_current = 0;
  }
  Check_vibro_state(Get_time_sleep());
}

void Check_vibro_state(int time_sleep){
  if(state_vibro_current == vibro_state_previous){
    vibro_state_previous = state_vibro_current;
    timer++;
    if(timer >= time_sleep * 120){
      state_vibro_sens = 0;
      timer = 0;
    }
  }
  if(state_vibro_current != vibro_state_previous){
    vibro_state_previous = state_vibro_current;
    state_vibro_sens = 1;
    timer = 0;
  }
}


bool GetVibroState(){
  return state_vibro_sens;
}

int Get_sleep_time_current(){
  return timer;
}
