
int inPin = 8; 
int btn1 = 7; 
int val = 0; 
int val2 = 0; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(inPin, OUTPUT);
  pinMode(btn1, INPUT_PULLUP); 
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(btn1);   // read the input pin
  //digitalWrite(ledPin, !val);

  if(val == 0 && val2 == 0) {
    Serial.println("zapal");
    val2 = 1;
    digitalWrite(inPin, HIGH);
    delay(200);
  } else if(val == 0 && val2 == 1) { 
    Serial.println("zgaś");   
    val2 = 0;
    digitalWrite(inPin, LOW);
    delay(200);
  }

  //Serial.println(val);

  // digitalWrite(inPin, HIGH);
  // delay(3000);
  // digitalWrite(inPin, LOW);
  // delay(3000);
  // Serial.println(val);
}
