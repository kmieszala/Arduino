#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int pinOut = 12;
int redPin = 6; // PINy z ~
int greenPin = 5;
int bluePin = 3;

#define COMON_ANODE;

const uint32_t km[] = {
		0x4a253,
		0x662a5224,
		0xa24a2000
};
const uint32_t happy[] = {
    0x19819,
    0x80000001,
    0x81f8000
};

void setup() {
  Serial.begin(9600);
  pinMode(pinOut, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  matrix.begin();
}

void loop() {
  matrix.loadFrame(km);
  
  digitalWrite(pinOut, HIGH);  
  delay(1000);
  int delayy = 200;
  int steps = 90;
  int step = 10;

  int x = 0;
  int y = steps/2;
  int z = steps;
  // 0+, steps/2+, steps-
  for(; x < steps/2; x+=step){
    setColor(x, y, z);
    y+=step;
    z-=step;
    delay(delayy);    
  }
  // steps/2+, steps-, steps/2-
  for(; x < steps; x+=step){
    setColor( x, y, z);
    y-=step;
    z-=step;
    delay(delayy);    
  }
  // steps-, steps/2-, 0+
  for(; x > steps/2; x-=step){
    setColor(x, y, z);
    y-=step;
    z+=step;
    delay(delayy);    
  }
  // steps/2-, 0+, steps/2+
  for(; x > 0; x-=step){
    setColor(x, y, z);
    y += step;
    z += step;
    delay(delayy);    
  }
  
  Serial.println("end");

  digitalWrite(pinOut, LOW);
  delay(1000);
}

void setColor(int red, int green, int blue){
  #ifdef COMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}
