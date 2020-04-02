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



void setup() {
  Serial.begin(115200);    
  Print_Version_Iron(2); //0 - 180* degrees(righthand), 2 - 0* degree(lefthand);
  delay(1000);
  Pin_Setup();
  Setup_PWM_Frequency(1); //0 - 10kHz(default), 1 - 60Hz(default), 2 - 5Hz
  Buzzing(); 
  Pin_INH(0);  //0 - off, 1 - on
  Pin_PWM(0);  //0 - off(0%), 1023 - on(100%)
}

void loop() {
  for(;;){
    Read_Input_Volt();
    Read_Btn();
    Main_Menu();
  }
}
