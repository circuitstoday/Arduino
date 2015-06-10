#Arduino

This is the Circuits Today official Repository for AVR and Arduino based micro controllers.

Below are the list and Details of each mini projects.
##ATtiny13 Software UART Tx
This project is inspired by the Arduino Software serial Library. It provides UART message Transmission Functionality to the ATtiny13. This is specially helpful if you are supposed to debug your ATtiny13 Project. It is mainly used to put up break points and register status so that user gets a hint of what is going inside of the microccontroller.
 >
 ##ATtiny13 IR Remote [NEC]
 This project Decodes NEC Remote's protocol. Commonly found in CAR audio systems. The Debugging is done with the Software UART Tx library and some adjustments are done in the code to match the performance [IC Specific]. A TSOP 1838 is used to receive the IR Pulses sen by the NEC Remote. It is useful for making remote control Switch Board and in small remote control Pojects.  
 >
 >##Uno Door Opener
 >It makes use of the [Arduino MFRC522 library](http://playground.arduino.cc/Learning/MFRC522) to interface MIFARE  MRFC522 Card reader. Upon Successfull authentication, it would provide access throught the door to the card holder.
