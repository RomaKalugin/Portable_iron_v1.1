#include <Wire.h>
#include "Read_Battery.h"
#include "READ_TEMPER.h"
#include "SETUP_PIN.h"
#include "BUZZING.h"
#include "PID.h"
#include "LCD_print.h"
#include "Set_Temp.h"
#include "Main_Menu.h"
#include "Switch_Menu.h"
#include "EEPROM_Read_Write.h"


static unsigned long current_time;
static unsigned long previous_time = 0;
static uint8_t interval_read_button = 500;


void setup() {
  Serial.begin(115200);    
  Print_Version_Iron(2); //0 - 180* degrees(righthand), 2 - 0* degree(lefthand);
  delay(1000);
  Pin_Setup();
  Setup_PWM_Frequency(1); //0 - 10kHz(default), 1 - 60Hz(default), 2 - 5Hz

  Print_Buzz();
  Pin_Buzz(1);
  delay(50);
  Pin_Buzz(0);
  //Buzzing(); 
  
  Pin_INH(0);  //0 - off, 1 - on
  Pin_PWM(0);  //0 - off(0%), 1023 - on(100%)
}

void loop() {
  for(;;){
    Read_Input_Volt();  //read input voltage (check voltage, when power supply is battery 3S)
    Read_Btn();
    current_time = millis();
    if (current_time - previous_time >= interval_read_button){
      previous_time = current_time;
      Print_BTN_value(Get_Btn_val());
    }
  } 
    //Main_Menu();
}
