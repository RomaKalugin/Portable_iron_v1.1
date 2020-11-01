#include "Setup_Pin.h"
#include "Arduino.h"

static const uint8_t INH = 3;
static const uint8_t PWM_OUT = 9;
//static const uint8_t LEFT_BTN = 4;
static const uint8_t BTN_pin = A7;
static const uint8_t BUZZ = 5;
static unsigned long current_time;
static unsigned long previous_time = 0;
static uint8_t interval_read_button = 20;

static uint8_t i = 0;

static uint16_t Btn_voltage = 0;
static uint8_t state_btn = 3;

void Setup_PWM_Frequency(int freq_type){
  switch(freq_type){
    case 0: 
    DDRB |= _BV(PB1) | _BV(PB2);        /* set pins as outputs */
    TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
    TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS10);                    /* no prescaling 15Khz */
    OCR1A = 0;
    ICR1 = 0x03ff;                      /* TOP counter value */

  break;
    case 1: 
  DDRB |= _BV(PB1) | _BV(PB2);        /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS12);                    /* prescaling  60Hz*/
  OCR1A = 0;
  ICR1 = 0x04ff;
  break;
    case 2: 
    DDRB |= _BV(PB1) | _BV(PB2);        /* set pins as outputs */
    TCCR1A = _BV(COM1A1) | _BV(COM1B1)  /* non-inverting PWM */
        | _BV(WGM11);                   /* mode 14: fast PWM, TOP=ICR1 */
    TCCR1B = _BV(WGM13) | _BV(WGM12)
        | _BV(CS12);                    /* prescaling 60Hz*/
  OCR1A = 0;
  ICR1 = 0x03ff;
  break;
  }
//TCCR1B = TCCR1B & B11111000 | B00000001; // set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
//
//TCCR1B = TCCR1B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
//
//TCCR1B = TCCR1B & B11111000 | B00000011; // for PWM frequency of 490.20 Hz (The DEFAULT)
//
//TCCR1B = TCCR1B & B11111000 | B00000100; // for PWM frequency of 122.55 Hz
//
//TCCR1B = TCCR1B & B11111000 | B00000101; // for PWM frequency of 30.64 Hz
}

void Pin_Setup(){
  pinMode(INH, OUTPUT);
  pinMode(BUZZ, OUTPUT);
  //pinMode(LEFT_BTN, INPUT);
  //pinMode(RIGHT_BTN, INPUT);
}

void Pin_PWM(int state_PWM){
    OCR1A = state_PWM; 
}

void Pin_INH(bool state_INH){
  switch(state_INH){
    case 0: digitalWrite(INH, LOW); break;
    case 1: digitalWrite(INH, HIGH); break;
    default: break;
  }
}

void Read_Btn(){
  Btn_voltage = 0;
  for(i = 0; i < 5; i++){
  Btn_voltage += analogRead(BTN_pin);
  delayMicroseconds(500);
  }
  Btn_voltage = Btn_voltage / i;
  Btn_voltage = ((Btn_voltage * 4.82) / 1024) * 1035;
  Check_state_btn(Btn_voltage);
}

int Get_Btn_val(){
  return Btn_voltage;
}


void Pin_Buzz(bool state_buzz){
  switch(state_buzz){
    case 0: analogWrite(BUZZ, 0); break;
    case 1: analogWrite(BUZZ, 100); break;
    default: break;
  }
}

void Check_state_btn(int voltage_on_button){
  if(voltage_on_button > 2300 && voltage_on_button < 2500){
    state_btn = 1;
  }
  if(voltage_on_button > 3300 && voltage_on_button < 3500){
    state_btn = 2;
  }
  if(voltage_on_button > 3550){
    state_btn = 3;
  }
}

int Get_state_btn(){
  return state_btn;
}
