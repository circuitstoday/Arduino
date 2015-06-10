### Attiny13 based Remote Control Decoder
This project Decodes NEC Remote's protocol. Commonly found in CAR audio systems. The Debugging is done with the Software UART Tx library and some adjustments are done in the code to match the performance [IC Specific]. A TSOP1838 is used to receive the IR Pulses sen by the NEC Remote. It is useful for making remote control Switch Board and in small remote control Pojects.
The algorithm is implemented in the file ```NEC_IR.h``` . And if you want to use the library, place the header file inside your project directory. Make an include statement with double quotes. However, few constants need to be calibrated before compiling. This includes the ```TSOP_PIN TSOP_PORT TSOP_DDR F_CPU ``` and ```PREMBLE```

__Usage:__
Place ```NEC_IR.h``` in your project directory and make an include statement
```#include"NEC_IR.h"```

Declare the input port and input pin to which TSOP1838 is connected  

Call the following function to get a decoded message
```getMessage()```

Toggle the LEDs. It depends upon the programming.

Tools used: WinAVR, Programmer's Notepad [Bundled with WINAVR], MFile [The MFile aka Makefile Editor, Bundled with the WinAVR], USBasp as a burner device, AVRdude as a burner software [ NOTE: USBasp is supported on AVRdude 5.1 or above, I had to download and replace the avrdude came bundled with WINavr ]

__About Copyright__. Well, if something is freely available, I believe it's only your consent which could stop using it, modify it, change it, distribute it in exchange or without money, or claim this work. I doesn't have any expectations from this file. I'd be happy if someone finds this helpful. Thank you.
