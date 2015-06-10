This program is used to emulate UART in ATtiny13. ATtiny13 doesn't have an inbuilt UART.
There is a software UART in Arduino. And this feature could be useful for debugging micro-controllers with few pins. I used an USB to ttl converter to receive the UART signal. You could make the program to send messages through UART.
I am using #define to define variables so that the program takes less space to compile. Actually, when you use #define, it is constant. By default, it would use PB0 pin (Define UART_PORT to change port, and define pin [0-7] to change pin) to send signals.
There are five methods with the following declaration:

void send(unsigned char data);
void printInt(unsigned int i);
void printStr(char *);			 // Always typecast. eg- printStr((char *)"Hello World!!!");
void printlnStr(char *ptr);  // Always typecast. eg- printlnStr((char *)"Hello World!!!");
void printHex(char ch);			 // Just 8 bit characters only

Usage instructions:
put this file in your source code folder and add declaration
#include"tiny13dbg.h"
[Use double quotes and not braces]

Define this three variable:
BAUD [Baud Rate]
UART_PORT [Port You will be using]
pin [pin you will be using]
note: Even you don't define these three, the settings are: BAUD=9600, UART_PORT=PORTB, pin=0

You might need to adjust the F_CPU for proper functioning of the system. The ATtiny13 is powered by internal RC Oscillator and it almost always deviates from the expected operating frequency.[Look into Makefile for the F_CPU Declaration]

Connect USB to ttl converter and Connect the PIN you are using to the Rx Pin of the UART TTL converter.

Use Putty or similar program to open the COM port. Open the com port corresponding to the TTL Converter.

Tools used: WinAVR, Programmer's Notepad [Bundled with WINAVR], MFile [The MFile aka Makefile Editor, Bundled with the WinAVR], USBasp as a burner device, AVRdude as a burner software [ NOTE: USBasp is supported on AVRdude 5.1 or above, I had to download and replace the avrdude came bundled with WINavr ]

And about copyrights. Well, if something is freely available, I believe it's only your consent which could stop using it, modify it, change it, distribute it in exchange or without money, or claim this work. I doesn't have any expectations from this file. I'd be happy if someone finds this helpful. Thank you.
