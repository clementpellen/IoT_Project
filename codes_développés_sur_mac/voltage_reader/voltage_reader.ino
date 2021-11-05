// TODO : PORQUOI PAS FAIRE UN TRUC DE CONFIG

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

const int input_voltage_pin = 13;

int input_voltage = 0;
int mapped_voltage = 0;

bool engine_state = false;

void readVoltage() {
  input_voltage = analogRead(input_voltage_pin);
}

void mapVoltage() {
  mapped_voltage = map(input_voltage, 0, 5000, 0, 100);
}

void displayVoltage() {
  Serial.println("Tension d'entrée");
  Serial.println(input_voltage);
}

void displayMappedVoltage() {
  Serial.println("Niveau de tension");
  Serial.print(mapped_voltage);
  Serial.println("%");
}

void defineEngineState() {
  mapped_voltage > 25 ? engine_state=true : engine_state=false;
}

void displayEngineState() {
  Serial.println("Etat de la machine");
  if(engine_state == true)
    Serial.println("HIGH");
  else 
    Serial.println("LOW");
}

void presentEngineState() {
  readVoltage();
  mapVoltage();
  defineEngineState();
  
  displayMappedVoltage();
  displayEngineState();
  Serial.println("");
}

void setup() {

  Serial.begin(115200);

  pinMode(input_voltage_pin, INPUT);

}

void loop() {

  presentEngineState();

  delay(1000);

}
