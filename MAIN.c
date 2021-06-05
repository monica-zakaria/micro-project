#include <stdbool.h>
#include "stdint.h"
#include <stdio.h>
#include "UART.h"
#include "LCD.h"
#include "GPS.h"
#include "led_and_button.h"

#include "E:/keil/EE319Kware/inc/tm4c123gh6pm.h"

void SystemInit () {}
	

int __main (void){
	
	uint8_t DIST = 110 ;
	uint8_t trial [5] = "meter";
	
    while (1){
    	
	  	led_button_init();
	  	led1_on(DIST);
   	
			
		lcd_init();
			
			LCD_WriteInteger(DIST);
			lcd_DATA(' ');
		LCD_writestring (trial);
				
		systick_delay(8000000);
			
		
		
	}	
}	