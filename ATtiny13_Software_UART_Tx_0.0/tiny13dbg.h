#ifndef _TINY13_DBG_H_
#define _TINY13_DBG_H_

void send(unsigned char data);
void sendInt(unsigned int i);    // PLease use printInt instead of send Int
void printInt(unsigned int i);
void printStr(char *);			 // Always typecast. eg- printStr((char *)"Hello World!!!")
void printlnStr(char *ptr);
void printHex(char ch);			 // Just 8 bit charachters only

void printHex(char ch){
	int i;
	for(i=4;i>=0;i-=4)
		((0x0F&(ch>>i))>9)?send('A'+(0x07&(ch>>i))):send('0'+(0x0F&(ch>>i)));
}
void printStr(char *ptr){
	while(*ptr!='\0'){
		send(*ptr);
		ptr++;
	}
}
void printlnStr(char *ptr){
	printStr(ptr);
	sendInt('\n');
}
void printInt(unsigned int i){
	i?sendInt(i):send('0');
}
void sendInt(unsigned int i){
	if(i){
		sendInt(i/10);
		send('0'+i%10);
	}
}

void send(unsigned char data){
#define BAUD 9600
#define sendDelay 1000000/BAUD
#ifndef UART_PORT
#define UART_PORT PORTB
#endif //UART_PORT
#ifndef pin
#define pin 0
#endif
#define Z	UART_PORT&=~(1<<pin)
#define O	UART_PORT|=(1<<pin)
	DDRB|=(1<<pin);
	Z;
	_delay_us(sendDelay);
	int i;
	for(i=0;i<8;i++){
		data&(1<<i)?O:Z;
		_delay_us(sendDelay);
	}
	O;
	_delay_us(sendDelay);
}

#endif //_TINY13_DBG_H_
