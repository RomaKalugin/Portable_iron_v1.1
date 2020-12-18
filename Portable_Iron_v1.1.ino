#include <Wire.h>
#include "Tasks.h"
#include "Read_Temper.h"
#include "Setup_Pin.h"
#include "Buzzing.h"
#include "PID.h"
#include "LCD_print.h"
#include "Switch_Menu.h"
//#include "EEPROM_Read_Write.h"


void setup() {
  Serial.begin(115200);    
  Print_Version_Iron(2); //0 - 180* degrees(righthand), 2 - 0* degree(lefthand);
  delay(2000);
  Clear_Display();
  Pin_Setup();
  Setup_PWM_Frequency(0); //0 - 15kHz(default), 1 - 60Hz(default), 2 - 5Hz

  Pin_Buzz(1);
  delay(50);
  Pin_Buzz(0);
  //Buzzing(); 
  
  Pin_INH(0);  //0 - off, 1 - on
  Pin_PWM(0);  //0 - off(0%), 1023 - on(100%)
}

void loop() {
  for(;;){
    Tasks();
  } 
    //Main_Menu();
}
