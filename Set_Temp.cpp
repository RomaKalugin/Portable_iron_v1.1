#include "Set_Temp.h"
#include "Read_Temper.h"
#include "Setup_Pin.h"
#include "Arduino.h"

static double temp;
static uint16_t temper_set;  // temperature in LSB 359 = 300 degree Celsius
static uint8_t step_temp = 5;
static uint16_t request_temper;
static uint16_t i = 0;
static uint16_t i_prev = 0;

int Get_Request_Temp(){
  return request_temper;
}
int Get_Temper_Set(){
  return temper_set;
}

void Set_Temp(int set_value){
  uint16_t adc_3 = analogRead(A3);
  Read_Temperature_ntc(adc_3, 23, 3950, 10000, 4700);
  temp = 0.0;
  temp = (((set_value - Get_Temp_ntc()) / 240.0) * 1024.0) / 4.84;
  temper_set = (int)temp;
}

void Request_Temper(){
  request_temper = Change_Temper(Get_Temper_Set());
}

/*int Read_Request_Temp(){
  Read_Btn();
  if (GetBtn_Left() == 1){
    temper_set--;
  }
  if (GetBtn_Right() == 1){
    temper_set++;
  }
  else ;
  return temper_set;
}*/

int Change_Temper(int temp_request){
  while (i < 800)
  {
     if(i_prev < temp_request && temp_request < i)
     {
        return i;
        i = 800;
     }
     i_prev = i;
     i = i + step_temp;    
  }
  i = 0;
}
