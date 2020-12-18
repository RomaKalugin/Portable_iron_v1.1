#include "Switch_Menu.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Vibrosens.h"
#include "Arduino.h"
#include "Read_Battery.h"

static uint8_t state_btn = 1;
static uint16_t start_tmp = 250;
static uint8_t tmp_up = 5;
static uint8_t tmp_dwn = 5;

/*******************************************/
static uint16_t counter_button = 0;
const static uint8_t counter_heat_state = 10;
const static uint8_t counter_battery_type_state = 10;
const static uint8_t counter_stndby_state = 10;
/*******************************************/

/*******************************************/
static uint8_t type_battery = 3; //default 3S-12.6V; 4S-16.8V; 5S-21V
/*******************************************/

void Check_state_stndby_btn(int voltage_on_button){
  if(state_btn == 1){

  if(voltage_on_button > 2300 && voltage_on_button < 2500){
    counter_button++;
    if(counter_button >= counter_battery_type_state){
      state_btn = 6;
      counter_button = 0;
    }
  }
  else if(voltage_on_button > 3300 && voltage_on_button < 3600){
    counter_button++;
    if(counter_button >= counter_heat_state){
      state_btn = 2;
      counter_button = 0;
    }
  }
  else if(voltage_on_button > 3650){
    counter_button++;
    if(counter_button >= counter_stndby_state){
      state_btn = 1;
      counter_button = 0;
    }
  }
  }
}

void Check_battery_state_btn(int voltage_on_button){
  static bool flag;

  if(state_btn == 6){
    if(voltage_on_button < 1000){
      flag = 0;
    }
    if(voltage_on_button > 2300 && voltage_on_button < 2500 && flag == 0){
     type_battery--;
     flag = 1;
      if(type_battery < 4){
        type_battery = 3;
      }
     }
    else if(voltage_on_button > 3300 && voltage_on_button < 3600 && flag == 0){
       type_battery++;
       flag = 1;
       if(type_battery > 4){
         type_battery = 5;
       } 
    }
    else if(voltage_on_button > 3650){
      counter_button++;
      if(counter_button >= counter_stndby_state){
        state_btn = 1;
        counter_button = 0;
      }
    }
  }
}

void Check_state_heat_btn(int voltage_on_button, int vibro_sens_state){
  static bool flag;

  if(state_btn == 2){
    if(voltage_on_button < 1000){
      flag = 0;
    }
    if(voltage_on_button > 3300 && voltage_on_button < 3600 && flag == 0){
      //delay(100);
      start_tmp = start_tmp + tmp_up;
      flag = 1;
    }
    else if(voltage_on_button > 2300 && voltage_on_button < 2500 && flag == 0){
      //delay(100);
      start_tmp = start_tmp - tmp_dwn;
      flag = 1;
    }
    if(voltage_on_button > 3650){
      counter_button++;
      if(counter_button >= counter_stndby_state){
        state_btn = 1;
        counter_button = 0;
      }
    }
    if(vibro_sens_state == 0){
      state_btn = 5;
    }
  }
  if(vibro_sens_state == 1){
      state_btn = 2;
      if(voltage_on_button > 3650){
        counter_button++;
        if(counter_button >= counter_stndby_state){
          state_btn = 1;
          counter_button = 0;
        }
      }
    }
}

int Get_type_battery(){
  return type_battery;
}

int Get_state_btn(){
  return state_btn;
}

int Get_request_temp(){
  return start_tmp;
}
