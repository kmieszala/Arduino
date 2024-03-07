#include "Arduino_LED_Matrix.h"
#include <Arduino_FreeRTOS.h>

ArduinoLEDMatrix matrix;

#define TRIG 2
#define ECHO 3
int buzzerPIN = 8;

float res = 100;

TaskHandle_t TaskHandleDistance;
TaskHandle_t TaskHandleBuzzer;

const uint32_t km[] = {
		0x4a253,
		0x662a5224,
		0xa24a2000
};

void setup() {
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(buzzerPIN, OUTPUT);
  Serial.begin(9600);
  matrix.begin();
  matrix.loadFrame(km);
  delay(1000);
  xTaskCreate(
                    distance,          /* Task function. */
                    "distance",        /* String with name of task. */
                    4*24,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    &TaskHandleDistance);            /* Task handle. */
  xTaskCreate(
                    makeSound,          /* Task function. */
                    "makeSound",        /* String with name of task. */
                    4*24,            /* Stack size in bytes. */
                    NULL,             /* Parameter passed as input of the task */
                    1,                /* Priority of the task. */
                    &TaskHandleBuzzer);            /* Task handle. */
 
  vTaskStartScheduler();
}

void loop() {}  

void makeSound(void * parameter){
  vTaskDelay( 1000 / portTICK_PERIOD_MS );  
  while(1) {   
    if(res > 11) {
      vTaskDelay(600);  
      tone(buzzerPIN, 0); 
    } else if(res > 9) {
      tone(buzzerPIN, 200);
      vTaskDelay(600);  
      tone(buzzerPIN, 0); 
    }else if(res > 7) {
      tone(buzzerPIN, 400);
      vTaskDelay(500);  
      tone(buzzerPIN, 0); 
    }else if(res > 5) {
      tone(buzzerPIN, 600);
      vTaskDelay(400); 
      tone(buzzerPIN, 0);  
    }else if(res > 3) {
      tone(buzzerPIN, 700);
      vTaskDelay(300);  
      tone(buzzerPIN, 0); 
    }else {
      tone(buzzerPIN, 900);   
      vTaskDelay(300);     
    }       
  }
}

void distance(void * parameter) {
  while(1) {    
    unsigned long time;
    digitalWrite(TRIG, HIGH);
    
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    time = pulseIn(ECHO, HIGH);
    res = time/58.00;
    vTaskDelay( 500 ); 
    Serial.println(res);
  }
}

