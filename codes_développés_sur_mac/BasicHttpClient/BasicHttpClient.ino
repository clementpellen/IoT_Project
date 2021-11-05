/**
 * BasicHTTPClient.ino
 *
 *  Created on: 24.05.2015
 *
 */


 // A ENVOYER : 
 // - identifiant de la machine
 // - state de la machine

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial

WiFiMulti wifiMulti;

/*
const char* ca = \ 
"-----BEGIN CERTIFICATE-----\n" \  
"MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \  
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \  
"DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \  
"SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \  
"GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \  
"AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \  
"q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \  
"SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \  
"Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \  
"a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \  
"/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \  
"AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \  
"CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \  
"bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \  
"c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \  
"VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \  
"ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \  
"MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \  
"Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \  
"AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \  
"uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \  
"wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \  
"X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \  
"PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \  
"KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \  
"-----END CERTIFICATE-----\n";
*/

const int engine_id = 1;

const int input_voltage_pin = 32;

int input_voltage = 0;
int mapped_voltage = 0;

bool engine_state = false;


////// VOLTAGE FUNCTIONS /////

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

bool determineEngineState() {
  int new_mapped_voltage = map(analogRead(input_voltage_pin), 0, 5000, 0, 100);
  if(new_mapped_voltage > 25) {
    return true;
  } 
  else 
    return false;
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

bool checkchangeState() {
  Serial.println("");
  Serial.print("Engine State : ");
  Serial.println(engine_state);
  Serial.print("DetermineEngineState : ");
  Serial.println(determineEngineState());
  Serial.println("");
  if(engine_state != determineEngineState())
    return true;
  else 
    return false;
}

void setup() {

    USE_SERIAL.begin(115200);

    pinMode(input_voltage_pin, INPUT);

    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for(uint8_t t = 4; t > 0; t--) {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("SFR-75e0", "QJDXPVQLQDU4");

}

void loop() {
    // wait for WiFi connection

    // Vérifie que l'état de la machine a évolué
    //if(checkchangeState()) {

      // Insère le nouvel état dans la variable globale
      defineEngineState();

      String server_request = "https://corner.soccer/iot/server.php/?engine_id=" + engine_id;
      server_request += "&is_on=";
      server_request += engine_state;

      Serial.println("TEST0");
        presentEngineState();

      if((wifiMulti.run() == WL_CONNECTED)) {

        Serial.println("TEST1");
        presentEngineState();

        HTTPClient http;

        USE_SERIAL.print("[HTTP] begin...\n");
        // configure traged server and url
        http.begin(server_request); //HTTPS

        USE_SERIAL.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        Serial.println("TEST2");
        presentEngineState();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                USE_SERIAL.println(payload);
            }
        } else {
            USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        Serial.println("TEST3");
        presentEngineState();

        http.end();

        Serial.println("");
        Serial.println("Inclusion réussie");
        Serial.println(server_request);
        Serial.println("");
    }
      
  //}

  presentEngineState();

  delay(5000);
}
