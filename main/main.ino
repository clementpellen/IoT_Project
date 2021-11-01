#include "includes.h"

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(9600);

  networkConnection(&WiFiMulti);
  
}

void loop() {

  // if(checkConnectionAvailable(&WiFiMulti)) {
    // sendDataToServer();
  // }

  delay(500);
  
}
