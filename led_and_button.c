
#include "led_and_button.h"

void led_button_init (void)
	{
		init(PORTF);
  
	}
	
	void led1_on (float distance ) {
		if (distance >= 100){ 
	GPIO_PORTF_DATA_R = 0x02 ; //led1 , pf1 ,[red led]
	}
}
	
	
	uint8_t get_button1_value(void){
	 return GPIO_PORTF_DATA_R &= 0x10  ; // pf4 switch1 for start 
	}
	uint8_t get_button2_value(void){
	 return GPIO_PORTF_DATA_R &= 0x01  ; // pf1 switch2 foe end 
	}