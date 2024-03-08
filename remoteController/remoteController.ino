#include "my_sign.h"
#include <IRremote.h>

int remotePin = 7;
int ledYellow = 3;
int ledWhite = 2;

IRrecv irrecv(remotePin);
decode_results results;

void setup() {
  addSign();
  pinMode(ledYellow, OUTPUT);
  pinMode(ledWhite, OUTPUT);

  IrReceiver.begin(remotePin, ENABLE_LED_FEEDBACK); // Start the receiver
  Serial.begin(9600);
}

void loop() {
  if (IrReceiver.decode()) {
      digitalWrite(ledWhite, HIGH);
      //Serial.println(IrReceiver.decodedIRData.decodedRawData); // Print "old" raw data
      Serial.println(IrReceiver.decodedIRData.address, HEX); // Print "old" raw data
      
      translateIR();
      IrReceiver.printIRResultShort(&Serial); // Print complete received data in one line
      //IrReceiver.printIRSendUsage(&Serial);   // Print the statement required to send this data
      
      IrReceiver.resume(); // Enable receiving of the next value
  }

  digitalWrite(ledYellow, LOW);
  digitalWrite(ledWhite, LOW);
}

void translateIR(){
  switch(IrReceiver.decodedIRData.decodedRawData){
  case 0xBA45FF00:  
    Serial.println(" CH-            "); 
    break;
  case 0xB946FF00:  
    Serial.println(" CH             "); 
    break;
  case 0xB847FF00:  
    Serial.println(" CH+            "); 
    break;
  case 0xBB44FF00:  
    Serial.println("PREV          "); 
    break;
  case 0xBF40FF00:  
    Serial.println("NEXT        "); 
    break;
  case 0xBC43FF00:  
    Serial.println("PLAY/PAUSE     "); 
    break;
  case 0xF807FF00:  
    Serial.println(" VOL-           "); 
    break;
  case 0xEA15FF00:  
    Serial.println(" VOL+           "); 
    break;
  case 0xF609FF00:  
    Serial.println(" EQ             "); 
    break;
  case 0xE916FF00:  
    Serial.println(" 0              "); 
    break;
  case 0xE619FF00:  
    Serial.println(" 100+           "); 
    break;
  case 0xF20DFF00:  
    Serial.println(" 200+           "); 
    break;
  case 0xF30CFF00:  
    Serial.println(" 1              "); 
    break;
  case 0xE718FF00:  
    Serial.println(" 2              "); 
    break;
  case 0xA15EFF00:  
    Serial.println(" 3              "); 
    break;
  case 0xF708FF00:  
    Serial.println(" 4              "); 
    break;
  case 0xE31CFF00:  
    Serial.println(" 5              "); 
    break;
  case 0xA55AFF00:  
    Serial.println(" 6              "); 
    break;
  case 0xBD42FF00:  
    Serial.println(" 7              "); 
    break;
  case 0xAD52FF00:  
    Serial.println(" 8              "); 
    break;
  case 0xB54AFF00:  
    Serial.println(" 9              "); 
    break;

  default: 
    digitalWrite(ledYellow, HIGH);
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    delay(1000);
  }

  delay(500);
}
