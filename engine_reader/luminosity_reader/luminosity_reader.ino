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

#include "esp32HttpClient.h"
#include "luminosity_reader_lib.h"


#define USE_SERIAL Serial


// Déclaration de l'objet Wifi
WiFiMulti wifiMulti;

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




void setup() {

  USE_SERIAL.begin(115200);

  pinMode(input_luminosity_pin, INPUT);

  networkConnection(&WiFiMulti);

}

void loop() {

  // Déclaration de la chaîne de caractères à insérer dans l'url
  String server_request = "https://corner.soccer/iot/server.php";

  defineEngineState();

  // Ajouter ici les variables à passer dans l'url

  if(checkConnectionAvailable(&WiFiMulti)) {
    sendDataToServer(server_request);
  }

  delay(5000);

}
