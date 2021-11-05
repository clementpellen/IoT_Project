#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial


const int red_led_output = 33;
const int green_led_output = 25;
const int blue_led_output = 26;

void turnOnRedLed() {
  digitalWrite(red_led_output, HIGH);
}

void turnOffRedLed() {
  digitalWrite(red_led_output, LOW);
}

void turnOnGreenLed() {
  digitalWrite(green_led_output, HIGH);
}

void turnOffGreenLed() {
  digitalWrite(green_led_output, LOW);
}

void turnOnBlueLed() {
  digitalWrite(blue_led_output, HIGH);
}

void turnOffBlueLed() {
  digitalWrite(blue_led_output, LOW);
}

void turnOnAllLeds() {
  digitalWrite(red_led_output, HIGH);
  digitalWrite(green_led_output, HIGH);
  digitalWrite(blue_led_output, HIGH);
}

void turnOffAllLeds() {
  digitalWrite(red_led_output, LOW);
  digitalWrite(green_led_output, LOW);
  digitalWrite(blue_led_output, LOW);
}

void turnOnRedLedOnly() {
  digitalWrite(red_led_output, HIGH);
  digitalWrite(green_led_output, LOW);
  digitalWrite(blue_led_output, LOW);
}

void turnOnGreenLedOnly() {
  digitalWrite(red_led_output, LOW);
  digitalWrite(green_led_output, HIGH);
  digitalWrite(blue_led_output, LOW);
}

void turnOnBlueLedOnly() {
  digitalWrite(red_led_output, LOW);
  digitalWrite(green_led_output, LOW);
  digitalWrite(blue_led_output, HIGH);
}

void showEngineOn() {
  turnOnGreenLedOnly();
}

void showEngineOff() {
  turnOnRedLedOnly();
}

void showDefaultConnection() {
  digitalWrite(red_led_output, HIGH);
  digitalWrite(green_led_output, HIGH);
  digitalWrite(blue_led_output, LOW);

  delay(2000);
  
  turnOffAllLeds();

  delay(300);
}

void showConnectionEstablished() {
  
  for(unsigned int i=0; i<10; ++i) {
    digitalWrite(red_led_output, HIGH);
    digitalWrite(green_led_output, HIGH);
    digitalWrite(blue_led_output, LOW);

    delay(150);

    turnOffAllLeds();

    delay(150);
  }
}

void setup() {

  pinMode(red_led_output, OUTPUT);
  pinMode(green_led_output, OUTPUT);
  pinMode(blue_led_output, OUTPUT);

  showConnectionEstablished();

}

void loop() {
  
  
}
