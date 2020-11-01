#ifndef _READ_TEMPER_H_
#define _READ_TEMPER_H_

int GetTemperature();
int Change_Reading_Temper(int temp_request);
double Get_Temp();
void Read_Temperature_Termocouple();
void Read_Temperature_ntc(int ADC_val, int temper_nominal, int B_coef, double series_resist, double thermistor_nomin);
int Get_Temp_ntc();

#endif
