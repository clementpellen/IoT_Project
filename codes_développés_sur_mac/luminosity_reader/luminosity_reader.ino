// TODO : PORQUOI PAS FAIRE UN TRUC DE CONFIG

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

const int input_luminosity_pin = 15;

int input_luminosity = 0;
int mapped_luminosity = 0;

bool engine_state = false;

void readLuminosity() {
  input_luminosity = analogRead(input_luminosity_pin);
}

void mapLuminosity() {
  mapped_luminosity = map(input_luminosity, 0, 4000, 0, 100);
}

void displayLuminosity() {
  Serial.println("Luminosité d'entrée");
  Serial.println(input_luminosity);
}

void displayMappedLuminosity() {
  Serial.println("Niveau de luminosité");
  Serial.print(mapped_luminosity);
  Serial.println("%");
}

void defineEngineState() {
  mapped_luminosity > 50 ? engine_state=true : engine_state=false;
}

void displayEngineState() {
  Serial.println("Etat de la machine");
  if(engine_state == true)
    Serial.println("HIGH");
  else 
    Serial.println("LOW");
}

void presentEngineState() {
  readLuminosity();
  mapLuminosity();
  defineEngineState();
  
  displayMappedLuminosity();
  displayEngineState();
  Serial.println("");
}

void setup() {

  Serial.begin(9600);

  pinMode(input_luminosity_pin, INPUT);


}

void loop() {

  presentEngineState();
  
  delay(1000);

}
