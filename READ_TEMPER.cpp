#include "Read_Temper.h"
#include "Arduino.h"

const float a = 0.0000007;
const float b = -0.001;
const float c = 1.04;
const float d = 24.602;
static uint16_t i = 0;
static uint16_t i_prev = 0;


static int16_t temperature_ntc = 0;

static uint16_t temperat_K;

const uint8_t ADC0 = A0;
static uint32_t val_ADC0 = 0;

static float temp;

int GetTemperature(){
  return temperat_K;
}

double Get_Temp(){
  return temp;
}

void Read_Temperature_Termocouple(){
  uint16_t adc_3 = analogRead(A3);
  Read_Temperature_ntc(adc_3, 23, 3950, 10000, 4700);
  //for(uint8_t i = 0; i < 5; i++){
  val_ADC0 = 0;
  static uint8_t i = 0; 
  for(i = 0; i < 30; i++){
  val_ADC0 += analogRead(ADC0);
  delay(1);
  }
  val_ADC0 = (((val_ADC0 / i) * 4.84) / 1024) * 175;
  temperat_K = val_ADC0 + Get_Temp_ntc();
  //temperat_K = val_ADC0;
//  Serial.println(temperat_K);
  //val_ADC0 = 0;
  //temp += a * (pow(temperat_K,3)) + b * (pow(temperat_K,2)) + c * temperat_K + d;
  //}
  //temp = temp / 5;

  //temperat_K = (int)temp;
}

int Change_Reading_Temper(int temp_request){
  while (i < 800)
  {
     if(i_prev < temp_request && temp_request < i)
     {
        return i;
        i = 800;
     }
     i_prev = i;
     i = i + 5 ;    
  }
  i = 0;
}

void Read_Temperature_ntc(int ADC_val, int temper_nominal, int B_coef, double series_resist, double thermistor_nomin){
  static double steinhart = 0.0;
  static float R2 = 0.0;
  static float logR2 = 0.0;
  steinhart = 0.0;
  R2 = series_resist / ((1024.0 / ADC_val) - 1);
  R2 = R2 / thermistor_nomin;
  logR2 = log(R2);
  steinhart = logR2 / B_coef;
  steinhart += 1.0 / (temper_nominal + 273.15);
  steinhart = 1.0 / steinhart;
  steinhart -= 273.15;
  temperature_ntc = (int)steinhart;
}

int Get_Temp_ntc(){
  return temperature_ntc;
}
