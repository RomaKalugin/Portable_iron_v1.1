#include "Tasks.h"
#include "Arduino.h"
#include "Read_Battery.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "Switch_Menu.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Buzzing.h"
#include "VibroSens.h"

static unsigned long current_time;
/*variable for 1 ms task*/
static unsigned long previous_time_1ms = 0;
static const uint8_t task_1ms = 1;
/*variable for 10 ms task*/
static unsigned long previous_time_10ms = 0;
static const uint8_t task_10ms = 10;
/*variable for 15 ms task*/
static unsigned long previous_time_15ms = 0;
static const uint8_t task_15ms = 15;
/*variable for 20 ms task*/
static unsigned long previous_time_20ms = 0;
static const uint8_t task_20ms = 20;
/*variable for 100 ms task*/
static unsigned long previous_time_100ms = 0;
static const uint8_t task_100ms = 100;
/*variable for 500 ms task*/
static unsigned long previous_time_500ms = 0;
static const uint16_t task_500ms = 500;

void Tasks(void){
  current_time = millis();
    if (current_time - previous_time_1ms >= task_1ms){
      previous_time_1ms = current_time;
      Task_1ms();
    }
    if (current_time - previous_time_10ms >= task_10ms){
      previous_time_10ms = current_time;
      Task_10ms();
    }
    if (current_time - previous_time_15ms >= task_15ms){
      previous_time_15ms = current_time;
      Task_15ms();
    }
    if (current_time - previous_time_20ms >= task_20ms){
      previous_time_20ms = current_time;
      Task_20ms(Get_state_btn());
    }
    if (current_time - previous_time_100ms >= task_100ms){
      previous_time_100ms = current_time;
      Task_100ms(Get_state_btn());
    }
    if (current_time - previous_time_500ms >= task_500ms){
      previous_time_500ms = current_time;
      Task_500ms(Get_state_btn());
    }
}

void Task_1ms(){
  
}

void Task_10ms(){
  
}

void Task_15ms(){
  
}
/*
Head function: 
Read button and switch menu
*/
void Task_20ms(int state_20ms){
  Read_Btn();
  switch(state_20ms){
    case 1: Check_state_stndby_btn(Get_Btn_val(), GetInputVolt(), Get_type_battery()); break;
    case 2: break;
    case 3: Check_state_stndby_btn(Get_Btn_val(), GetInputVolt(), Get_type_battery()); break;
    case 4: break;
    case 5: Check_state_heat_btn(Get_Btn_val(), GetVibroState()); break;
    case 6: Check_battery_state_btn(Get_Btn_val()); break;
    case 7: break;
    case 8: Check_sleep_state_btn(Get_Btn_val()); break;
    default: break;
  }
}

//static uint16_t tmp_thermocouple;
void Task_100ms(int state_100ms){
  switch(state_100ms){
    case 1: break;
    case 2: Pin_INH(0); Check_state_heat_btn(Get_Btn_val(), GetVibroState()); delay(15); Read_Temperature_Termocouple(); Pin_INH(1); Update_PID(); Pin_PWM(GetOutput()); break;
    case 3: break;
    case 4: break;
    case 5: Pin_INH(0); delay(15); Read_Temperature_Termocouple(); Pin_INH(1); Update_PID(); Pin_PWM(GetOutput()); break;
    case 6: break;
    default: break;
  }
}

void Task_500ms(int state_500ms){
  Read_Input_Volt(); /*read input voltage (check voltage, when power supply is battery 3S/4S/5S/24V)*/
  switch(state_500ms){
    case 1: Pin_INH(0); Standby_LCD(); break;
    case 2: Check_Input_Voltage(GetInputVolt(), Get_type_battery()); Tracking_vibro(); Print_Heat(GetTemperature(), Get_request_temp()); break;
    case 3: Pin_INH(0); Buzzing(); Print_min_volt(GetInputVolt()); break;
    case 4: Pin_INH(0); Print_Start_Temp(250); break;
    case 5: Pin_INH(0); /*delay(9); Read_Temperature_Termocouple();*/ Print_sleep(GetTemperature()); break;
    case 6: Pin_INH(0); Print_Type_Battery(Get_type_battery()); break;
    case 7: Pin_INH(0); Print_Buzzing(1); break;
    case 8: Pin_INH(0); Print_Time_sleep(Get_time_sleep()); break;
    default: break;
  }
}
