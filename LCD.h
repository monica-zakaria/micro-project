#include "stdint.h"
#include "E:/keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "SYSTICKTIMER.h"
#include "PORTS_INIT.h"


void lcd_command(uint8_t command);
void lcd_DATA(uint8_t character);
void lcd_init(void);
void LCD_WriteInteger(uint32_t intgr);
void LCD_writestring(uint8_t* str);
