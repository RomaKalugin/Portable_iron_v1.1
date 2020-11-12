#include "Read_Battery.h"
#include "Arduino.h"
#include "Buzzing.h"
#include "LCD_print.h"

const static uint8_t read_input_volt = A2;
static uint16_t input_voltage = 0;

void Read_Input_Volt(){
  static uint8_t i = 0;
  input_voltage = 0;
  for(i = 0; i < 10; i++){
  input_voltage += analogRead(read_input_volt);
  }
  input_voltage = input_voltage / i;
  input_voltage = ((input_voltage * 24.3) / 1024) * 1035;
  //Check_Input_Voltage(GetInputVolt());
}

void Check_Input_Voltage(int check_volt){
  if(check_volt < 10000){}
  else if(check_volt > 10000 ){}
}

int GetInputVolt(){
  return input_voltage;
}
