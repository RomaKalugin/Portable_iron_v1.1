#include "Tasks.h"
#include "Arduino.h"
#include "Read_Battery.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "Switch_Menu.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Set_Temp.h"
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
      Task_20ms();
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
void Task_20ms(){
  Read_Btn();
  //Main_Menu();
}

//static uint16_t tmp_thermocouple;
void Task_100ms(int state_100ms){
  switch(state_100ms){
    case 1: break;
    case 2: Pin_INH(0); Check_state_heat_btn(Get_Btn_val(), 0, GetVibroState()); delay(11); Read_Temperature_Termocouple(); Pin_INH(1); Update_PID(); Pin_PWM(GetOutput()); break;
    case 3: break;
    case 4: break;
    case 5: Check_state_heat_btn(Get_Btn_val(), 0, GetVibroState()); break;
  }
}

void Task_500ms(int state_500ms){
  //uint16_t adc_3 = analogRead(A3);
  //Print_value(GetVibroState());
  Tracking_vibro();
  switch(state_500ms){
    case 1: Pin_INH(0); Read_Input_Volt(); /*read input voltage (check voltage, when power supply is battery 3S)*/ break;
    case 2: Print_Heat(GetTemperature(), Get_request_temp()); /*Print_BTN_value(/*Get_Temp_ntc()*/ /*GetTemperature(), Get_request_temp());*/ /*Read_Temperature_ntc(adc_3, 23, 3950, 10000, 4700);*//*Standby_LCD();*/  break;
    case 3: Print_BTN_value(GetInputVolt(), 0); Pin_INH(0); break;
    case 4: Print_min_volt(GetInputVolt()); Buzzing(); Pin_INH(0); break;
    case 5: Pin_INH(0); Read_Temperature_Termocouple(); Print_sleep(GetTemperature()); break;
  }
}
