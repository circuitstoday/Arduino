#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include"tiny13dbg.h"

int main(void){	
	
	while(1){
	
		_delay_ms(1000);
		send('R');
		send('A');
		send('K');
		send('E');
		send('S');
		send('H');
		send(' ');
		
		printStr((char *)"Bute ");
		
		printHex('0');
		
		send(' ');
		
		printInt(1000); // unsigned int only
		
		send('\n');
	 }
	return 0;
}
