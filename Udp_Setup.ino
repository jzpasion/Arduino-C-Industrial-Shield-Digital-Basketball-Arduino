const int btnstart = 25;    




int buttonState2;            
int lastButtonState2 = LOW;   

unsigned long lastDebounceTime2 = 0;  
unsigned long debounceDelay2 = 50;   



void StartButton() {

if (StartState == "Start"){
  return;
}
  int strtbtn = digitalRead(btnstart);


  if (strtbtn != lastButtonState2) {

    lastDebounceTime2 = millis();
  }

  if ((millis() - lastDebounceTime2) > debounceDelay2) {

    if (strtbtn != buttonState2) {
      buttonState2 = strtbtn;


      if (buttonState2 == HIGH) {
       Serial.println("Start");
   
       udp_sends("Start");
         udp_check();
      }
    }
  }

  lastButtonState2 = strtbtn;
}
