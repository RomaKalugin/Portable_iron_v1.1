#ifndef _SETUP_PIN_H_
#define _SETUP_PIN_H_

void Pin_Setup();
void Setup_PWM_Frequency(int freq_type);
void Pin_PWM(int state_PWM);
void Pin_INH(bool state_INH);
void Read_Btn();
int Get_Btn_val();
void Pin_Buzz(bool state_buzz);



#endif
