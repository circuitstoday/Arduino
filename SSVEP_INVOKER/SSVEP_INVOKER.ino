

//boolean ledStates[4] = {false,false,false,false};
int pins[4]= {2,3,4,5};
unsigned int freqs[4]= {15,18,21,24};
void setup() {
  for(int i=0;i<=3;i++){
    pinMode(pins[i],OUTPUT);
    digitalWrite(pins[i],1);
  }
  Serial.begin(9600);
}

void loop() {
  volatile unsigned int mills=millis();
  for(volatile int i=0;i<=3;i++)
    ((volatile unsigned int) mills*freqs[i]%1000)==((volatile unsigned int) mills*freqs[i]%500)?digitalWrite(pins[i],1):digitalWrite(pins[i],0);
}
