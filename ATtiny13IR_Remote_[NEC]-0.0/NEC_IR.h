#ifndef _NEC_IR_H_
#define _NEC_IR_H_

#ifndef TSOP_PIN
#define TSOP_PIN 4
#endif
#ifndef TSOP_PORT
#define TSOP_PORT PIN
#endif
#ifndef TSOP_DDR
#define TSOP_DDR	DDRB
#endif
#define PREMBLE	 54

#define KEY_0			0xFF97
#define KEY_1			0xFFCF
#define KEY_2			0xFFE7
#define KEY_3			0xFF85
#define KEY_4			0xFFEF
#define KEY_5			0xFFC7
#define KEY_6			0xFFA5
#define KEY_7			0xFFBD
#define KEY_8			0xFFB5
#define KEY_9			0xFFAD
#define KEY_100_PLUS	0xFF67
#define KEY_200_PLUS	0xFF4F
#define KEY_VOL_UP		0xFF57
#define KEY_VOL_DN		0xFF1F
#define KEY_PREV		0xFFDD
#define KEY_NEXT		0xFFFD
#define KEY_PLAY_PAUSE	0xFF3D
#define KEY_CHANNEL		0xFF9D
#define KEY_CHANNEL_UP	0xFF1D
#define KEY_CHANNEL_DN	0xFF5D

unsigned int pulseWidth(uint8_t HL);
uint16_t getMessage();
unsigned int waitFor(uint8_t HL);

uint16_t getMessage(){
	waitFor(0);
	waitFor(1);
	uint8_t i[33];
	uint8_t j=0;
	uint32_t result=0;
	i[0]=pulseWidth(1);
	if(i[0]>=PREMBLE){
		for(j=1;j<=32;j++){
			i[j]=pulseWidth(1);
		}
		for(j=1;j<=32;j++){
			result=result<<1;
			result|=(((i[j])>i[0]/4)?1:0);
		}
		return (uint16_t)((0x00ff0000&result)>>8)|(0x000000ff&result);
	}
	else return 0;
}
unsigned int waitFor(uint8_t HL){
unsigned int i=0;
	while(HL?(!(TSOP_PORT&(1<<TSOP_PIN))):(TSOP_PORT&(1<<TSOP_PIN))){
		_delay_us(1);
		i++;
	}
	return i;
}
unsigned int pulseWidth(uint8_t HL){
			HL?waitFor(1):waitFor(0);
	return	HL?waitFor(0):waitFor(1);
}
#endif // _NEC_IR_H_
