#include "EEPROM_Read_Write.h"
#include "Arduino.h"
#include "EEPROM.h"
#include "avr/eeprom.h"

int eeprom_value;

void Write_EEPROM(int address, int value){
  EEPROM.put(address, value / 4);
}


void Check_EEPROM(){
  
}

void Calc_Value_from_eeprom(int address){
  EEPROM.get(address, eeprom_value);
}

int GetValue_int(){
  eeprom_value;
}

float GetValue_float(){
  
}
