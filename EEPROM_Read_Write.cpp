#include "EEPROM_Read_Write.h"
#include "Arduino.h"
#include "EEPROM.h"
//#include "avr/eeprom.h"

static uint16_t get_from_eeprom_temperature_at_start; //address 0-2 bytes
static uint8_t get_from_eeprom_minutes_to_sleep;      //address 2-1 byte 
static uint8_t get_from_eeprom_left_or_right_hand;    //address 3-1 byte
static uint8_t get_from_eeprom_type_battery;          //address 4-1 byte

void Write_EEPROM(int address, int value){
  switch(address){
    case 0: EEPROM.put(address, value); break;
    case 2: EEPROM.put(address, value); break;
    case 3: EEPROM.put(address, value); break;
    case 4: EEPROM.put(address, value); break;
    default: break;
  }
}

void Check_EEPROM(){
  
}

void Get_value_from_eeprom(int address){
  switch(address){
    case 0: EEPROM.get(address, get_from_eeprom_temperature_at_start); break;
    case 2: EEPROM.get(address, get_from_eeprom_minutes_to_sleep); break;
    case 3: EEPROM.get(address, get_from_eeprom_left_or_right_hand); break;
    case 4: EEPROM.get(address, get_from_eeprom_type_battery); break;
    default: break;
  } 
}

int Get_temperature_at_start_from_eeprom(){
  return get_from_eeprom_minutes_to_sleep;
}

int Get_time_to_sleep_from_eeprom(){
  return get_from_eeprom_minutes_to_sleep;
}

float GetValue_float(){
  
}
