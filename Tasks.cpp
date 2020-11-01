#include "Tasks.h"
#include "Arduino.h"
#include "Read_Battery.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "Main_Menu.h"
#include "PID.h"
#include "Read_Temper.h"

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
/*variable for 190 ms task*/
static unsigned long previous_time_190ms = 0;
static const uint8_t task_190ms = 190;
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
    if (current_time - previous_time_190ms >= task_190ms){
      previous_time_190ms = current_time;
      Task_190ms(Get_state_btn());
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
  Main_Menu();
}

void Task_190ms(int state_190ms){
  switch(state_190ms){
    case 1: Update_PID(); break;
  }
}

void Task_500ms(int state_500ms){
  Read_Input_Volt();  //read input voltage (check voltage, when power supply is battery 3S)
  uint16_t adc_3 = analogRead(A3);
  switch(state_500ms){
    case 3: Print_BTN_value(GetInputVolt()); break;
    case 1: Read_Temperature_ntc(adc_3, 23, 3950, 10000, 4700);/*Standby_LCD();*/ Print_BTN_value(Get_Temp_ntc());break;
  }
}
