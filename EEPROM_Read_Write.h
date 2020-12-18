#ifndef _EEPROM_Read_Write_H_
#define _EEPROM_Read_Write_H_

void Write_EEPROM(int address, int value);
void Check_EEPROM();
void Calc_Value_from_eeprom(int address);
int GetValue_int();
float GetValue_float();

#endif
