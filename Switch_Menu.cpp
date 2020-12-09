#include "Switch_Menu.h"
#include "Setup_Pin.h"
#include "Set_Temp.h"
#include "LCD_print.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Vibrosens.h"
#include "Arduino.h"

static uint8_t state_btn = 3;
static uint16_t start_tmp = 250;
static uint16_t tmp_up = 5;
static uint16_t tmp_dwn = 5;

void Check_state_stndby_btn(int voltage_on_button, int input_voltage){
  if(state_btn == 3){
  if(voltage_on_button > 2300 && voltage_on_button < 2500){
    state_btn = 1;
  }
  else if(voltage_on_button > 3300 && voltage_on_button < 3600){
    state_btn = 2;
  }
  else if(voltage_on_button > 3650){
    state_btn = 3;
  }
  }
}

void Check_state_heat_btn(int voltage_on_button, int input_voltage){
  //do{
  //Print_text_size1(Get_request_temp());
  //}while(0);
  
  if(state_btn == 2){
    if(voltage_on_button > 3300 && voltage_on_button < 3600){
      //delay(100);
      start_tmp = start_tmp + tmp_up;
    }
    else if(voltage_on_button > 2300 && voltage_on_button < 2500){
      //delay(100);
      start_tmp = start_tmp - tmp_dwn;
    }
    else if(voltage_on_button > 3650){
      state_btn = 3;
    }
  }
  //if(input_voltage < 9000){
  //  state_btn = 4;
  //}
  //else if(input_voltage >= 9000){ //checking input voltage(use 3S battery)
  //  state_btn = 3;
  //}
}

int Get_state_btn(){
  return state_btn;
}

int Get_request_temp(){
  return start_tmp;
}
