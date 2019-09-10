const int buttonPin = 22;    
const int buttonPin2 = 23;
const int buttonPin3 = 24;

      
int lastButtonState = LOW;   
int TopState = LOW;
unsigned long topTime = 0;

String buttonState;    
String Status;
String Static = "NO PRESSED!";
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 
   
String StartState = "End";


String inputString = "";
boolean stringComplete = false;

void setup() {
   udp_setup();
  Serial.begin(9600);
  inputString.reserve(200);
  pinMode(buttonPin, INPUT);
    pinMode(buttonPin2, INPUT);
      pinMode(buttonPin3, INPUT);

}

void loop() {
   int reading = digitalRead(buttonPin);
      int reading2 = digitalRead(buttonPin2);
        int reading3 = digitalRead(buttonPin3);
        
StartButton();
udp_check();

 if(reading == HIGH && reading2 == HIGH){
  TopState = reading;
  topTime = millis();
  

 }else if (reading == HIGH && reading2 != HIGH){
  Status = "One Clear";
 }else if (reading2 == HIGH && reading != HIGH){
    Status = "One Clear";
 }

if((millis() - topTime) < 3000){
  
  if(TopState == HIGH){
     if(reading3 == HIGH){
      Status = "Clear";
     }
    }else{
      TopState = LOW;
     }
  
}
 
 if (Status != Static) {
    lastDebounceTime = millis();
  }
 

if ((millis() - lastDebounceTime) > debounceDelay) {

    if (Status != buttonState) {
      buttonState = Status;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == "Clear") {
        if(StartState == "Start"){
         udp_sends(Status);
         Serial.println("Points");
         Serial.println(StartState);
         }else{
          return;
         }

      }
    }
  }
   Static = Status;
   
}


void serialEvent(){
  while(Serial.available()){
    char inChar = (char)Serial.read();
    inputString += inChar;
    if(inChar == '\n'){
      stringComplete = true;
    }
  }
}
  
