#include "PID.h"
#include "Read_Temper.h"
#include "LCD_print.h"
#include "Arduino.h"
#include "Set_Temp.h"
#include "Switch_Menu.h"

static float Kp = 35.0;
static float Ki = 0.018;
static float Kd = 0.0;

static float deriv;

static float error;
static float last_error;
static float err_sum = 0;

static unsigned long timer;
static unsigned long timer_up;

static int16_t output;
 
static float windup = 0.0000095;
static float sat_diff;
static int16_t satur_low = 0;
static int16_t satur_high = 1023;

void Update_PID(){
  timer = millis();
  //for(uint8_t i = 0; i < 5; i++){
  //Read_Temperature_Termocouple();
  //}
  //Set_Temp(100);
  error = Get_request_temp() - GetTemperature();
 // Serial.println(GetTemperature());
  err_sum += error;
  deriv = (error - last_error) / (timer - timer_up);
  output = (Kp * error) + (Ki * err_sum) + (Kd * deriv);
  if(output > satur_high){
    sat_diff = satur_high - output;
    err_sum += windup * sat_diff;
    output = satur_high;
  }
  else if (output <= satur_low){
    sat_diff = satur_low - output;
    err_sum += windup * sat_diff;
    output = satur_low;
  }
  last_error = error;
  timer_up = timer;
}

int GetOutput(){
  return output;
}
