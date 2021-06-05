#include "stdint.h"
#include "E:/keil/EE319Kware/inc/tm4c123gh6pm.h"
#include "PORTS_INIT.h"

void UART0_INIT (void);
void UART0_TRANSMIT (uint8_t data);
uint8_t UART0_Receive (void) ; 

void UART2_INIT (void);
void UART2_TRANSMIT (uint8_t data);
uint8_t UART2_Receive (void) ; 