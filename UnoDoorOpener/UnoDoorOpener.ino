#include <EEPROM.h>
#include <Servo.h>
#include <MFRC522.h>
#include <SPI.h>

MFRC522 reader(10,9);
Servo doorOpener;

#define DB_FLASH_TIME_OUT 14000

void setup(){  
  Serial.begin(9600);
  SPI.begin();
  reader.PCD_Init();
  doorOpener.attach(8);
  initDB();
  pinMode(2,INPUT_PULLUP);
  
  Serial.println("RFID Door opener");
}

void loop(){
  int i=0;
  if ( ! reader.PICC_IsNewCardPresent()&& !switchIsOn()) {
                delay(500);
		return;
	}
  processCard();
}

void processCard(){
  int cardsRead=0;
  int i=0;
  uint32_t UIDlist[6];
  uint32_t tempUID;
  boolean oldCard;
  oldCard=false;
  do{
    if(reader.PICC_ReadCardSerial()){
      for(i=0;i<=reader.uid.size;i++)
        tempUID=(tempUID<<8)|reader.uid.uidByte[i];
    for(i=0;i<cardsRead;i++)
      if(tempUID==UIDlist[i])
        oldCard=true;    
    if(oldCard){
      break;
    }
    else{
      UIDlist[cardsRead]=tempUID;
      cardsRead++;
    }
    }
    else
      break;
  }while(cardsRead<=6&&reader.PICC_IsNewCardPresent());
 
  Serial.print(cardsRead);
  Serial.println(" Cards red.");  
  for(i=0;i<cardsRead;i++)
    Serial.println(UIDlist[i],HEX);  
  Serial.print("Switch State: ");
  Serial.println(switchIsOn(),HEX);
 
  /* Vital Functions
   *
   */
  if(cardsRead==1&&!switchIsOn()){ //Complete
    if(DB_CardIndex(UIDlist[0])&&DB_StoredCard()){
      Serial.print("Door opened by authentic card: ");
      Serial.println(UIDlist[0],HEX);
      openDoor();
    }
    else if(!DB_StoredCard()){
      DB_StoreCard(UIDlist[0]);
      if(DB_CardIndex(UIDlist[0])&&DB_StoredCard()){
        Serial.print("Cards added for fresh Start: ");
        Serial.println(UIDlist[0],HEX);
        openDoor();
      }
    }
    else{
      Serial.println("Not an authentic Card" );
      delay(2000);
    }
  }
  else if(switchIsOn()&&cardsRead==0){ //Complete
    Serial.println("Door opened on Button Press.");
    openDoor();
  }
  else if(switchIsOn()&&cardsRead==1){ // Suspectful, for removal of cards
    
    /*
     *
     * Data base flash logic
     *
     */
    
    
    delay(DB_FLASH_TIME_OUT);
    if(!(reader.PICC_ReadCardSerial()||reader.PICC_ReadCardSerial())){
      flushDB();
      DB_StoreCard(UIDlist[0]);
      Serial.print("Database Flushed by card: ");
      Serial.println(UIDlist[0],HEX);
      delay(2000);
    }
    else{
      DB_DelCard(UIDlist[0]);
      Serial.print("Card removed from Database: ");
      Serial.println(UIDlist[0],HEX);
      delay(2000);
    }
  }
  else if(switchIsOn()&&cardsRead>=1){ // Complete
    int authCards=0;
    int k=0;
    for(k=0;k<=cardsRead;k++)
      if(DB_CardIndex(UIDlist[k])){
        authCards++;
      }
    if(authCards==1){
      int j;
      for(j=0;j<cardsRead;j++){
        DB_StoreCard(UIDlist[j]);
        Serial.print("Card Added to Database: ");
        Serial.println(UIDlist[j],HEX);
        delay(2000);
      }
    }
    else{      
      Serial.println("Multiple Authentic Cards present for special operation. ");
      delay(2000);
    }
  }
  else{
    Serial.println("No or multiple authentic card is present."); 
    delay(2000);
  }
}
