#include "Switch_Menu.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Vibrosens.h"
#include "Arduino.h"
#include "Buzzing.h"
#include "Read_Battery.h"

static uint8_t state_btn = 1;
static uint16_t start_tmp = 250;
static uint16_t start_tmp_previous = 0;
static uint8_t tmp_up = 5;
static uint8_t tmp_dwn = 5;

/*******************************************/
static uint16_t counter_button = 0;
const static uint8_t counter_heat_state = 10;
const static uint8_t counter_battery_type_state = 10;
const static uint8_t counter_time_sleep_state = 20;
const static uint8_t counter_stndby_state = 10;
/*******************************************/

/*******************************************/
static uint8_t type_battery = 3; //default 3S-12.6V; 4S-16.8V; 5S-21V
/*******************************************/

/*******************************************/
static uint8_t time_sleep = 5; //default 5 min - max 15 min
/*******************************************/


void Check_state_stndby_btn(int voltage_on_button, int input_voltage, int type_battery){

  if(state_btn == 1){

  if(voltage_on_button > 2300 && voltage_on_button < 2500){
    counter_button++;
  }
  else if(voltage_on_button < 1000){
    if(counter_button >= counter_battery_type_state && counter_button < counter_time_sleep_state){
      state_btn = 6;
      counter_button = 0;
    }
    if(counter_button >= counter_time_sleep_state && counter_button > counter_battery_type_state){
      state_btn = 8;
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
      if(type_battery > 23){
        type_battery = 6;
      }
     type_battery--;
     flag = 1;
      if(type_battery < 4){
        type_battery = 3;
      }
    }
    else if(voltage_on_button > 3300 && voltage_on_button < 3600 && flag == 0){
       type_battery++;
       flag = 1;
       if(type_battery > 5){
         type_battery = 24;
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

void Check_sleep_state_btn(int voltage_on_button){
  static bool flag;

  if(state_btn == 8){
    if(voltage_on_button < 1000){
      flag = 0;
    }
    if(voltage_on_button > 2300 && voltage_on_button < 2500 && flag == 0){
     time_sleep--; // in minutes
     flag = 1;
      if(time_sleep < 1){ 
        time_sleep = 1;
      }
     }
    else if(voltage_on_button > 3300 && voltage_on_button < 3600 && flag == 0){
       time_sleep++;
       flag = 1;
       if(time_sleep > 15){
         time_sleep = 15;
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
      if(start_tmp > 450){
        start_tmp = 450;
      }
      flag = 1;
    }
    else if(voltage_on_button > 2300 && voltage_on_button < 2500 && flag == 0){
      //delay(100);
      start_tmp = start_tmp - tmp_dwn;
      if(start_tmp < 100){
        start_tmp = 100;
      }
      flag = 1;
    }
    start_tmp_previous = start_tmp;
    if(voltage_on_button > 3650){
      counter_button++;
      if(counter_button >= counter_stndby_state){
        state_btn = 1;
        counter_button = 0;
      }
    }
    if(vibro_sens_state == 0){
      state_btn = 5;
      start_tmp = 200; ///EEPROM
    }
  }
  if(vibro_sens_state == 1){
      state_btn = 2;
      start_tmp = start_tmp_previous;
      if(voltage_on_button > 3650){
        counter_button++;
        if(counter_button >= counter_stndby_state){
          state_btn = 1;
          counter_button = 0;
        }
      }
    }
}

void Check_Input_Voltage(int check_volt, int type_battery){
  switch(type_battery){
  case 3: if(check_volt < 9000){ state_btn = 3;}
          if(check_volt > 9000 ){Pin_Buzz(0);} 
          break;
  case 4: if(check_volt < 12000){ state_btn = 3;}
          if(check_volt > 12000 ){Pin_Buzz(0);} 
          break;
  case 5: if(check_volt < 15000){ state_btn = 3;}
          if(check_volt > 15000 ){Pin_Buzz(0);}
          break;
  case 24: if(check_volt < 9000){state_btn = 3;}
           if(check_volt > 9000){Pin_Buzz(0);} 
  default: break;
  }
}

int Get_type_battery(){
  return type_battery;
}

int Get_time_sleep(){
  return time_sleep;
}

int Get_state_btn(){
  return state_btn;
}

int Get_request_temp(){
  return start_tmp;
}
