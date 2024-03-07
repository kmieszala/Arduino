#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

byte frame[8][12] = {
  { 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0 },
  { 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0 },
  { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 },
  { 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};

int segA = 11;int segB = 7;int segC = 4;int segD = 2;
int segE = 1;int segF = 10;int segG = 5;
int pinDP = 3; int digit1 = 12; int digit2 = 9; int digit3 = 8; int digit4 = 6;
int analogPin  = A0;  
int val = 0;

#define DIGIT_ON  LOW
#define DIGIT_OFF  HIGH
#define DISPLAY_BRIGHTNESS  400

boolean duiz = false;
boolean hon = false;

//int segPD = ; 
void setup() { 
  matrix.begin();

  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);
  pinMode(pinDP, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  matrix.renderBitmap(frame, 8, 12);
  val = analogRead(analogPin);  // read the input pin

  delay(2000);
  Serial.println(val);
  
  printOnMatrix(val);

  digitalWrite(pinDP, HIGH);

  for(int y = 2 ; y > 0 ; y--) {  
    onDigit(y);
    for(int x = 0 ; x < 5 ; x++) {  
      lightNumber(x);
      delay(DISPLAY_BRIGHTNESS);
    }
  }

  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);
}

void printOnMatrix(int val) {
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 12; j++){
      frame[i][j] = 0;
    }
  }

  matrix.renderBitmap(frame, 8, 12);
  delay(DISPLAY_BRIGHTNESS);

  setNumber(0, val / 100);
  int x = val % 100;
  setNumber(4, x / 10);
  x = x % 10;
  setNumber(8, x);

  matrix.renderBitmap(frame, 8, 12);
  delay(DISPLAY_BRIGHTNESS);
}

void setNumber(int col, int val) {
  switch(val){
    case 0:
      putLine(col);
      putLine(col + 2);
      frame[1][col + 1] = 1;
      frame[5][col + 1] = 1;
      break;
    case 1:
      putLine(col + 2);
      break;
    case 2:
      frame[1][col] = 1;
      frame[4][col] = 1;
      frame[2][col + 2] = 1;
      frame[1][col + 1] = 1;
      frame[1][col + 2] = 1;
      frame[3][col] = 1;
      frame[3][col + 1] = 1;
      frame[3][col + 2] = 1;
      frame[5][col] = 1;
      frame[5][col + 1] = 1;
      frame[5][col + 2] = 1;
      break;
    case 3:
      putLine(col + 2);
      frame[1][col] = 1;
      frame[1][col + 1] = 1;
      frame[3][col] = 1;
      frame[3][col + 1] = 1;
      frame[5][col] = 1;
      frame[5][col + 1] = 1;
      break;
    case 4:
      putLine(col + 2);
      frame[1][col] = 1;
      frame[2][col] = 1;
      frame[3][col] = 1;
      frame[3][col + 1] = 1;
      break;
    case 5:
      frame[1][col] = 1;
      frame[1][col + 1] = 1;
      frame[1][col + 2] = 1;
      frame[2][col] = 1;
      frame[3][col] = 1;
      frame[4][col + 2] = 1;
      frame[3][col + 1] = 1;
      frame[3][col + 2] = 1;
      frame[5][col + 2] = 1;
      frame[5][col + 1] = 1;
      frame[5][col] = 1;
      break;
    case 6:
      putLine(col);
      frame[1][col + 1] = 1;
      frame[1][col + 2] = 1;
      frame[3][col + 1] = 1;
      frame[3][col + 2] = 1;
      frame[4][col + 2] = 1;
      frame[5][col + 1] = 1;
      frame[5][col + 2] = 1;
      break;
    case 7:
      putLine(col + 2);
      frame[1][col] = 1;
      frame[1][col + 1] = 1;
      break;
    case 8:
      putLine(col);
      putLine(col + 2);
      frame[1][col + 1] = 1;
      frame[3][col + 1] = 1;
      frame[5][col + 1] = 1;
      break;
    case 9:
      putLine(col + 2);
      frame[1][col] = 1;
      frame[2][col] = 1;
      frame[1][col + 1] = 1;
      frame[3][col] = 1;
      frame[3][col + 1] = 1;
      frame[5][col] = 1;
      frame[5][col + 1] = 1;
      break;
    }
}


void putLine(int col) {
  frame[1][col] = 1;
  frame[2][col] = 1;
  frame[3][col] = 1;
  frame[4][col] = 1;
  frame[5][col] = 1;
}

void onDigit(int digit) {
  switch(digit) {
    case 1:
      digitalWrite(digit1, HIGH);  
      break;
    case 2:
      digitalWrite(digit2, HIGH);  
      break;
    case 3:
      digitalWrite(digit3, HIGH);  
      break;
    case 4:
      digitalWrite(digit4, HIGH);  
      break;
  }
}

void lightNumber(int numberToDisplay) {

  #define SEGMENT_ON  LOW
  #define SEGMENT_OFF HIGH
  switch (numberToDisplay){

  case 0:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 1:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 2:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 3:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 4:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 5:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 6:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 7:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;

  case 8:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_ON);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 9:
    digitalWrite(segA, SEGMENT_ON);
    digitalWrite(segB, SEGMENT_ON);
    digitalWrite(segC, SEGMENT_ON);
    digitalWrite(segD, SEGMENT_ON);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_ON);
    digitalWrite(segG, SEGMENT_ON);
    break;

  case 10:
    digitalWrite(segA, SEGMENT_OFF);
    digitalWrite(segB, SEGMENT_OFF);
    digitalWrite(segC, SEGMENT_OFF);
    digitalWrite(segD, SEGMENT_OFF);
    digitalWrite(segE, SEGMENT_OFF);
    digitalWrite(segF, SEGMENT_OFF);
    digitalWrite(segG, SEGMENT_OFF);
    break;
  }
}
