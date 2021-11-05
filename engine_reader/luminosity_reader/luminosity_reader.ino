/**
 * 
 * Ce code réalise 3 tâches principales :
 *    - Lire la luminosité de l'indicateur de fonctionnement de la machine
 *    - Indiquer au serveur en ligne si la machine est en fonctionnement
 *    - Indiquer visuellement si la machine est en fonctionnement à l'aide d'une LED
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#define USE_SERIAL Serial


// Déclaration de l'objet Wifi
WiFiMulti WiFiMulti;

// Déclaration de l'identifiant de la machine
const int engine_id = 1;

// Déclaration du pin chargé de lire la valeur de la luminosité 
// du témoin de fonctionnement de la machine
const int input_luminosity_pin = 35;

// Déclaration des variables de valeur de la luminosité (absolues et en %)
int input_luminosity = 0;
int mapped_luminosity = 0;


// VARIABLE DESIGNANT SI LA MACHINE    //
// EST EN FONCTGIONNEMENT OU A L'ARRET //
bool engine_state = false;



//////////////////////////
//                      //
//    Esp32HTTPClient   //
//                      //
//////////////////////////

void networkConnection() {
  
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    WiFiMulti.addAP("SFR-75e0", "QJDXPVQLQDU4");
}

boolean checkConnectionAvailable()
{
    // wait for WiFi connection
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void sendDataToServer(String server_request)
{

    HTTPClient http;

    USE_SERIAL.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(server_request); //HTTPS

    USE_SERIAL.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        USE_SERIAL.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            String payload = http.getString();
            USE_SERIAL.println(payload);
        }
    }
    else
    {
        USE_SERIAL.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    //Serial.println("");
    //Serial.println("Inclusion réussie");
    //Serial.println(server_request);
    //Serial.println("");
}



//////////////////////////
//                      //
//  LUMINOSITY READER   //
//                      //
//////////////////////////

////// LUMINOSITY FUNCTIONS /////

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

  USE_SERIAL.begin(115200);

  pinMode(input_luminosity_pin, INPUT);

  networkConnection();

}

void loop() {

  // Déclaration de la chaîne de caractères à insérer dans l'url
  String server_request = "https://corner.soccer/iot/server.php";

  defineEngineState();

  // Ajouter ici les variables à passer dans l'url

  if(checkConnectionAvailable()) {
    sendDataToServer(server_request);
  }

  delay(5000);

}
