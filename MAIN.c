#include <stdbool.h>
#include "stdint.h"
#include <stdlib.h>
#include <stdio.h>
#include "UART.h"
#include "LCD.h"
#include "GPS.h"
#include "math.h"
#include "led_and_button.h"

#include "E:/keil/EE319Kware/inc/tm4c123gh6pm.h"
#define CPAC (*((volatile uint32_t *)0xE000ED88))
void SystemInit() {
	CPAC |= 0X00F00000;
}


float DISTANCE;
uint32_t JUST;
uint8_t TEST;
uint8_t SEND;
static bool flag_start = false;

//char at [3] = "1.2" ;
int __main(void) {

	uint8_t x[8] = "DISTANCE";
	float lat1 = 0;
	float latf = 0;
	DISTANCE = 0;
	JUST = 0;
	led_button_init();
	UART0_INIT();
	UART5_INIT();
	UART2_INIT();
	lcd_init();
	LCD_writestring(x);
	lcd_DATA(' ');
	while (1) {
		flag_start = false;

		if (get_button2_value() == 0) {//sw2 pressed
			flag_start = true;
			while (1) {

				TEST = UART2_Receive(); //FROM GPS

				gps_string(TEST);

				if (get_button1_value() == 0) {

					break;
				}
			}

		}
		//3SECS
		systick_delay(16000000); //1s
		systick_delay(16000000); //1s
		systick_delay(16000000); //1s
		if (flag_start == true) {
			DISTANCE = return_distance();

			JUST = DISTANCE;
			if (JUST == 0)
			{
				LCD_writestring("ZER0");
			}
			LCD_WriteInteger(JUST);
			lcd_DATA('m');
			led1_on(DISTANCE);
			SEND = UART5_Receive();
			if (SEND == 'U')
			{
				send_uart();
			}
		}

		//if (UART5_Receive() == 'U'){
		//send_uart ();}
	}
}