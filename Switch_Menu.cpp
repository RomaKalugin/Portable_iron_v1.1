#include "Switch_Menu.h"
#include "Setup_Pin.h"
#include "Set_Temp.h"
#include "LCD_print.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Vibrosens.h"
#include "Arduino.h"

static uint8_t state_menu = 0;
static uint8_t state_heat = 0;

/* variable for temper_set*/
static uint16_t previous_temper = 0;
static uint16_t temper = 300;           // 300 degree(default)
static const uint16_t temper_max = 450; // 450 degree 
static const uint16_t temper_min = 100;  // 100 degree
static const uint16_t temp_step = 1;    // 
/********************************/

/* variable for temper_preset_set*/
static uint16_t temper_preset = 300; // 300 degree(default)
static const uint16_t temper_preset_max = 450;
static const uint16_t temper_preset_min = 100;
/********************************/

/* variables for switch_main_menu */
static unsigned long time_up = 0;
static uint32_t interval_preset_temp = 200000;
static uint32_t interval_standby_mode = 300000;
/**********************************/

/* variables for update_pid */
static unsigned long timer;
static unsigned long previous_time_pid = 0;
static const uint8_t interval_update_pid = 190;
/****************************/

/**/
static unsigned long previous_time_print_temp = 0;
static const uint16_t interval_update_print_temp = 500;
/**/

/**/
static unsigned long previous_time_set_request_temp = 0;
static const uint8_t interval_set_request_temp = 150;
/**/

/**/
static unsigned long previous_time_print_state = 0;
static const uint8_t interval_print_state = 15;
/**/

/* variable for back_to_state_0 */
static uint32_t time_up_two = 0;
/********************************/

/**/
static int16_t Temperature;
static int16_t RequestTemperature;
static int16_t PreviousTemperature = 0;
/**/

/**/
static uint32_t timer_current = 0;
/**/

/*
static unsigned long timer = 0;
static unsigned long prev_time = 0;
*/

/*void Switch_Main_Menu(){
  if(GetBtn_Right() == HIGH && GetBtn_Left() == LOW){
    time_up++;
  }
  else if(GetBtn_Right() == LOW){
    //Serial.println(time_up);
    if (time_up < 40000 && time_up > 500){ state_menu = 1;}
    else if(interval_preset_temp > time_up && time_up > 50000){ state_menu = 2;}
    else if(interval_standby_mode > time_up && time_up > interval_preset_temp){state_menu = 3;}
    time_up = 0;
  }
}*/

/*void Switch_Back_to_State_0(){
  if(GetBtn_Right() == HIGH && GetBtn_Left() == HIGH){
    time_up_two++;
    //Serial.print("Time_up_2Button   =   ");
    //Serial.println(time_up_two);                                             // улучшить чтение времени // привязка ко времени
  }
  else if (GetBtn_Right() == LOW && GetBtn_Left() == LOW && state_menu != 0){
    if(time_up_two > 300){state_menu = 0;}
    time_up_two = 0;
  }
}*/

/*void Switch_Set_Preset_Temp(){
  Set_Temp(temper);
  if(state_menu == 3 && GetBtn_Right() == HIGH){
    temper = temper + temp_step;
    if(temper > temper_max){temper = temper_max; Set_Temp(temper); Request_Temper(); Print_Max(Get_Request_Temp()); delay(500);}
    Set_Temp(temper); 
  }
  if(state_menu == 3 && GetBtn_Left() == HIGH){
    temper = temper - temp_step;
    if(temper < temper_min){temper = temper_min; Set_Temp(temper); Request_Temper(); Print_Min(Get_Request_Temp()); delay(500);}
    Set_Temp(temper);
  }
  Request_Temper();
  Print_Request_Temp(Get_Request_Temp());
}

void Switch_Heating_Set_Temp(){
  timer_current++;
  //Set_Temp(temper);
  if(timer_current >= 1000){
    state_menu = 1;
    timer_current = 0;
  }
  if (state_menu == 2 && GetBtn_Left() == HIGH && GetBtn_Right() == HIGH){
    state_menu = 0; Pin_INH(0); Pin_PWM(0);
  }
  else if (state_menu == 2 && GetBtn_Right() == HIGH){
    temper = temper + temp_step;
    timer_current = 0;
    if(temper > temper_max){temper = temper_max;
    Set_Temp(temper);}
  }
  else if(state_menu == 2 && GetBtn_Left() == HIGH){
    temper = temper - temp_step;
    if(temper < temper_min){temper = temper_min;}
    Set_Temp(temper);
    timer_current = 0;
  }
  else if(state_menu == 2 && (GetBtn_Right() == HIGH || GetBtn_Left() == HIGH)){
    Set_Temp(temper);
    Request_Temper();
    Print_Request_Temp(Get_Request_Temp());
   }
}

void State_Heating(){
  timer = millis();
  Pin_PWM(GetOutput());                                                                                                 
  Switch_Back_to_State_0();
  if(timer - previous_time_pid > interval_update_pid){
    previous_time_pid = timer;
    state_heat = 1;
    }
  else if(timer - previous_time_set_request_temp > interval_set_request_temp){
  previous_time_set_request_temp = timer;
  if(state_menu == 1 && (GetBtn_Right() == HIGH || GetBtn_Left() == HIGH)){  
    state_heat = 3; 
    }
  }   
  else if(timer - previous_time_print_temp > interval_update_print_temp){
    previous_time_print_temp = timer;
    state_heat = 2;
    Tracking_vibro();
  }
  else if(timer - previous_time_print_state >= interval_print_state){ 
    previous_time_print_state = timer;
    if(Temperature - PreviousTemperature > 5 && PreviousTemperature < Temperature){Print_Heating();}
    else if(Temperature > RequestTemperature){Print_Heat();} 
    else if(Temperature - PreviousTemperature < -5 && PreviousTemperature > Temperature){Print_Cooling();}
    PreviousTemperature = Temperature;
  }
  else if(GetVibroState() == true){
    state_heat = 4;
  }
  else if(GetVibroState() == false){
    state_heat = 5;
  }
  previous_temper = temper;
}*/

void Switch_State_Heating(int state_heating){
  switch(state_heating){
    case 0: break;
    case 1: Pin_INH(0); /*delay(10);*/ Update_PID(); Pin_INH(1); break;
    case 2: Set_Temp(temper); Request_Temper(); Temperature = GetTemperature(); RequestTemperature = Get_Temper_Set(); Print_Temp(); break;
    case 3: state_menu = 2; Pin_INH(0); break;
    case 4: temper = 200; break;
    case 5: temper = previous_temper; break;
    case 6: break;
    default: break;  
  }
}


int GetState_Menu(){
return state_menu;
}

int GetRequestTemp(){
	return temper;
}
