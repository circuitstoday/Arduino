
boolean switchIsOn(){
 if(!digitalRead(2)){
   return true;
 }
 else {
   return false;
 }
}

void openDoor(){
  doorOpener.write(0);
  delay(4000);
  while(!doorClosed());
  doorOpener.write(90);
}

boolean doorClosed(){
 return true ;
}
