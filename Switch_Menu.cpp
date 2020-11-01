#include "Switch_Menu.h"
#include "Setup_Pin.h"
#include "Set_Temp.h"
#include "LCD_print.h"
#include "PID.h"
#include "Read_Temper.h"
#include "Vibrosens.h"
#include "Arduino.h"



void Switch_Main_Menu(){
  
}

void Switch_Back_to_State_0(){
  
}

void Switch_Set_Preset_Temp(){
  
}

void Switch_Heating_Set_Temp(){
  
}

void State_Heating(){
  
}

void Switch_State_Heating(int state_heating){
  switch(state_heating){
    case 0: break;
    case 1: Pin_INH(0); /*delay(10);*/ Update_PID(); Pin_INH(1); break;
    case 2: Set_Temp(/*temper*/0); Request_Temper(); /*Temperature = GetTemperature(); RequestTemperature = Get_Temper_Set();*/ Print_Temp(); break;
    case 3: /*state_menu = 2;*/ Pin_INH(0); break;
    case 4: //temper = 200; break;
    case 5: //temper = previous_temper; break;
    case 6: break;
    default: break;  
  }
}


int GetState_Menu(){
  
}

int GetRequestTemp(){
  
}
