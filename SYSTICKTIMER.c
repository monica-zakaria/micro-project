#include "SYSTICKTIMER.h"

void systick_delay(uint32_t cycles) //max delay 1 sec
{
NVIC_ST_CTRL_R =0; //inialization with zero all registers
NVIC_ST_RELOAD_R = 0X00FFFFFF; //MAX RELOAD VALUE FOR INITIALIZATION
NVIC_ST_CURRENT_R=0; //clear value of register and flag counter
NVIC_ST_CTRL_R = 0x5; // enable 101
NVIC_ST_RELOAD_R = cycles -1; //timer value
NVIC_ST_CURRENT_R=0; //clear value of register and flag counter
while ((NVIC_ST_CTRL_R & 0x00010000) == 0){} //checking the flag if equals 1;
}


