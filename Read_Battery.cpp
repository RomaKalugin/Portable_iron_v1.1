#include "Read_Battery.h"
#include "Arduino.h"

const uint8_t read_input_volt = A2;
static double input_voltage;

void Read_Input_Volt(){
  input_voltage = 0;
  for(uint8_t i = 0; i < 10; i++){
   input_voltage += analogRead(read_input_volt);
    }
    input_voltage = input_voltage / 10;
    input_voltage = input_voltage * (24 / 1023); 
}

void Check_Input_Voltage(double check_volt){
  if(check_volt < 10.0){/*Print_min_volt(GetInputVolt());*/}
  else if(check_volt > 10.0 ){}
}

double GetInputVolt(){
  return input_voltage;
}
