#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int redPin = 6; // PINy z ~
int greenPin = 5;

#define COMON_ANODE;

const uint32_t km[] = {
		0x4a253,
		0x662a5224,
		0xa24a2000
};

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  matrix.begin();
}

void loop() {
  matrix.loadFrame(km);
  //digitalWrite(redPin, LOW); // LOW = ON
  //digitalWrite(greenPin, LOW);
  //analogWrite(redPin, -255);
  lightsOn();
}

void lightsOn(){
  int delayy = 200;
  int steps = 90;
  int step = 10;

  int x = 0;
  int y = steps/2;
  if(y%10 != 0){
    y-=y%10;
  }
  // 0+, steps/2+, steps-
  for(; x < steps/2; x+=step){
    setColor(x, y);
    y+=step;   
    delay(delayy);    
  }
  Serial.println((String)"x:"+x+" y:"+y);
  // steps/2+, steps-, steps/2-
  for(; x < steps; x+=step){
    setColor( x, y);
    y-=step;
    delay(delayy);    
  }
  Serial.println((String)"x:"+x+" y:"+y);
  // steps-, steps/2-, 0+
  for(; x > steps/2; x-=step){
    setColor(x, y);
    y-=step;
    delay(delayy);    
  }
  Serial.println((String)"x:"+x+" y:"+y);
  // steps/2-, 0+, steps/2+
  for(; x > 0; x-=step){
    setColor(x, y);
    y += step;
    delay(delayy);    
  }
  
  Serial.println("end");

  delay(1000);
}

void setColor(int red, int green){
  #ifdef COMON_ANODE
    red = 255 - red;
    green = 255 - green;
  #endif

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
}
