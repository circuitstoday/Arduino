#include<avr/io.h>
#include<util/delay.h>
#include "NEC_IR.h"
 
int main(void){
	DDRB=0x0F;
	while(1){
		_delay_ms(100);
		switch(getMessage()){
			case KEY_1:	PORTB^=(1<<0); break;
			case KEY_2:	PORTB^=(1<<1); break;
			case KEY_3:	PORTB^=(1<<2); break;
			case KEY_4:	PORTB^=(1<<3); break;
		}
	 }
	return 0;
}

