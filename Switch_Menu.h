#ifndef _Switch_Menu_
#define _Switch_Menu_

void Check_state_stndby_btn(int voltage_on_button);
void Check_battery_state_btn(int voltage_on_button);
void Check_state_heat_btn(int voltage_on_button, int vibro_sens_state);

int Get_state_btn();
int Get_type_battery();
int Get_request_temp();


#endif
