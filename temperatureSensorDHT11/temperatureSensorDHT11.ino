#include "Arduino_LED_Matrix.h"
#include <DHT.h>
#include <DHT_U.h>

ArduinoLEDMatrix matrix;
#define DHTTYPE    DHT11  
#define DHTPIN 2 

DHT_Unified dht(DHTPIN, DHTTYPE);

const uint32_t km[] = {
		0x4a253,
		0x662a5224,
		0xa24a2000
};

void setup() {
  Serial.begin(9600);
  dht.begin();
  matrix.begin();
  matrix.loadFrame(km);
}

void loop() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println(F("Error reading humidity!"));
  }
  else {
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
  }

  delay(2000);

}

