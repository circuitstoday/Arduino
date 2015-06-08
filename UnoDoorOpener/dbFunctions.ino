
#define DB_START 210
#define DB_SIZE  32

uint32_t UID_LI;
uint32_t CARD;

uint32_t DB_CardIndex(uint32_t cardUID){
 uint32_t search=1;
 while(search<=DB_StoredCard()){
  if(DB_GetCard(search)==cardUID)
    return search;
  search++; 
 }
 return 0; 
}

uint8_t DB_StoreCard(uint32_t cardUID){
  if(DB_StoredCard()>=DB_SIZE)
    return 2;
  else{
    if(!DB_CardIndex(cardUID)){
      ROM_Write32(DB_START+sizeof(uint32_t)*(DB_StoredCard()+1),cardUID);
      ROM_Write32(DB_START,ROM_Read32(DB_START)+1);
      return 0;
    }
  }
}

void initDB(){
  if(ROM_Read32(DB_START)==0x00000000||ROM_Read32(DB_START)==0xFFFFFFFF)
  ROM_Write32(DB_START,0);
}

void flushDB(){
  ROM_Write32(DB_START,0);
}

uint8_t DB_DelCard(uint32_t cardNo_DB){
  if(cardNo_DB>DB_StoredCard())
    return 1;
  else if(DB_StoredCard()==0)
    return 2;
  else if(cardNo_DB<=0)
    return 3;
  else{    
    do{
      ROM_Write32(DB_START+sizeof(uint32_t)*cardNo_DB,ROM_Read32(DB_START+sizeof(uint32_t)*(cardNo_DB+1)));
      cardNo_DB++;
    }while(cardNo_DB<DB_StoredCard());    
    ROM_Write32(DB_START+sizeof(uint32_t)*(DB_StoredCard()),0x00000000);
    ROM_Write32(DB_START,ROM_Read32(DB_START)-1);
    return 0;
  }
}

uint32_t DB_GetCard(uint32_t cardNumber){
  if(cardNumber>DB_StoredCard())
    return 1;
  else if(DB_StoredCard()==0)
    return 2;
  else if(cardNumber<=0)
    return 3;
  else
    return ROM_Read32(DB_START+sizeof(uint32_t)*cardNumber);
}

uint32_t DB_StoredCard(){
 return ROM_Read32(DB_START); 
}

uint8_t ROM_Write32(uint16_t startingAddress,uint32_t data){
  uint8_t count=sizeof(uint32_t);  
  do{
    count--;
  EEPROM.write(startingAddress+count,(uint8_t)data&0x000000ff);
  data=data>>0x08;
  delay(3.5);
  }while(count);
  return 0;
}

uint32_t ROM_Read32(uint16_t startingAddress){
  uint32_t data=0;
  uint8_t  count=sizeof(uint32_t);
  do{   
    data=data<<0x08|EEPROM.read(startingAddress+sizeof(uint32_t)-count);
    count--;
  }while(count);
  return data;
}
