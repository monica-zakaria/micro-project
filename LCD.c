#include "LCD.h"


// D0-D7 [PORT B] , RS [port A pin 5 ] , Rw [port A pin 6 ] , E [port A pin 7 ]
void lcd_command(uint8_t command){
GPIO_PORTA_DATA_R &=~0x60; //RS = 0 [command], RW = 0 [write]
GPIO_PORTB_DATA_R = command ; // write command
GPIO_PORTA_DATA_R |=0x80; // ENABLE 
	
systick_delay(32000); //delay 2ms

GPIO_PORTA_DATA_R &=~0x80; // DISABLE	
	
}
void lcd_DATA(uint8_t character){
GPIO_PORTA_DATA_R &=~ 0x40; // RW = 0 [write]
GPIO_PORTA_DATA_R |= 0x20; // RS = 1 [data]
GPIO_PORTB_DATA_R = character; //write data
	
GPIO_PORTA_DATA_R |= 0x80; // ENABLE 
systick_delay(32000); //delay 2ms

GPIO_PORTA_DATA_R &=~ 0x80; // DISABLE	
	
}

void lcd_init(void){
systick_delay(800000);//delay 50ms


  init (PORTB);	
	init(PORTA);
	
lcd_command(0x38) ; // 8_bit data
     systick_delay(16000); //delay 1ms
			
lcd_command(0x0E)  ; // increment curcur 
systick_delay(32000); //delay 2ms

lcd_command(0x01) ; 

systick_delay(32000); //delay 2ms
	lcd_command(0x06)	 ;	// display on 

systick_delay(16000); //delay 1ms
}
void LCD_WriteInteger(uint32_t intgr) {

	uint32_t y = 1;


	while (intgr > 0)
	{
		y = ((y * 10) + (intgr % 10));
		intgr /= 10;
	}

	while (y > 1)
	{
		lcd_DATA(((y % 10) + 48));
		y /= 10;
	}
}
void LCD_writestring(uint8_t * str) {

	uint8_t i = 0;
	while (str[i] != '\0')
	{
		lcd_DATA(str[i]);
		i++;
	}
}
