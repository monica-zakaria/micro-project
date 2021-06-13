#include "UART.h"

///////////////////// UART 0 [TIVA C & PC] A0 RX , A1 TX
void UART0_INIT (void){
	
SYSCTL_RCGCUART_R |= 0x0001; // activate UART0
	init(PORTA);

UART0_CTL_R &= ~0x0001; // disable UART
UART0_IBRD_R = 104; // IBRD=int(16000000/(16*9600)) = int(104.1666) 
UART0_FBRD_R = 11; // FBRD = (0.1666 * 64)+0.5 = 11
UART0_LCRH_R = 0x0070; // 8-bit word length, enable FIFO
UART0_CTL_R = 0x0301; // enable RXE, TXE and UART

}


// Wait for buffer to be not full, then output
void UART0_TRANSMIT (uint8_t data){
	while((UART0_FR_R&0x0020) != 0); // wait until TXFF is 0
UART0_DR_R = data;	
}
// Wait for new input, then return ASCII code
uint8_t UART0_Receive (void){
while((UART0_FR_R&0x0010) != 0); // wait until RXFE is 0
	
return((char)(UART0_DR_R&0xFF));

} 
///////////////////// UART 2 [TIVA C & GPS] D6 RX , D7 TX
void UART2_INIT (void){
	
SYSCTL_RCGCUART_R |= 0x0004; // activate UART2
init(PORTD);
UART2_CTL_R &= ~0x0001; // disable UART
UART2_IBRD_R = 104; // IBRD=int(16000000/(16*9600)) = int(104.1666) 
UART2_FBRD_R = 11; // FBRD = (0.1666 * 64)+0.5 = 11
UART2_LCRH_R = 0x0070; // 8-bit word length, enable FIFO
UART2_CTL_R = 0x0301; // enable RXE, TXE and UART

}


// Wait for buffer to be not full, then output
void UART2_TRANSMIT (uint8_t data){
	while((UART2_FR_R&0x0020) != 0); // wait until TXFF is 0
UART2_DR_R = data;	
}
// Wait for new input, then return ASCII code
uint8_t UART2_Receive (void){
while((UART2_FR_R&0x0010) != 0); // wait until RXFE is 0
	
return((char)(UART2_DR_R&0xFF));

}

///////////////////// UART 5 [TIVA C & PC with TTL] E4 RX , E5 TX
void UART5_INIT(void) {

	SYSCTL_RCGCUART_R |= 0x0020; // activate UART5
	init(PORTE);
	UART5_CTL_R &= ~0x0001; // disable UART
	UART5_IBRD_R = 104; // IBRD=int(16000000/(16*9600)) = int(104.1666) 
	UART5_FBRD_R = 11; // FBRD = (0.1666 * 64)+0.5 = 11
	UART5_LCRH_R = 0x0070; // 8-bit word length, enable FIFO
	UART5_CTL_R = 0x0301; // enable RXE, TXE and UART

}


// Wait for buffer to be not full, then output
void UART5_TRANSMIT(uint8_t data) {
	while ((UART5_FR_R & 0x0020) != 0); // wait until TXFF is 0
	UART5_DR_R = data;
}
// Wait for new input, then return ASCII code
uint8_t UART5_Receive(void) {
	while ((UART5_FR_R & 0x0010) != 0); // wait until RXFE is 0
  //systick_delay(10);
	return((char)(UART5_DR_R & 0xFF));

}