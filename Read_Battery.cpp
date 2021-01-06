#include "Read_Battery.h"
#include "Arduino.h"
#include "Buzzing.h"
#include "Setup_Pin.h"
#include "LCD_print.h"
#include "Switch_Menu.h"

const static uint8_t read_input_volt = A2;
static uint32_t input_voltage = 0;

void Read_Input_Volt(){
  static uint8_t i = 0;
  input_voltage = 0;
  for(i = 0; i < 20; i++){
  input_voltage += analogRead(read_input_volt);
  //delay(2);
  }
  input_voltage = input_voltage / i;
  input_voltage = ((input_voltage * 24.3) / 1024) * 1058;
  //Check_Input_Voltage(GetInputVolt(), Get_type_battery());
}



int GetInputVolt(){
  return input_voltage;
}
