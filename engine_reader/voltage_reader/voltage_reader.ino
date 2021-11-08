/**
 * 
 * Ce code réalise 3 tâches principales :
 *    - Lire la tension de la partie commande de la machine
 *    - Indiquer au serveur en ligne si la machine est en fonctionnement
 *    - Indiquer visuellement si la machine est en fonctionnement à l'aide d'une LED
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>

#include <HTTPClient.h>

#include "SPIFFS.h"

#include "MD5.h"

#include "time.h"


// Déclaration de l'objet Wifi
WiFiMulti WiFiMulti;

// Déclaration de la variable vérifiant si la connexion est établie
bool connection_established = false;

// Déclaration de l'identifiant de la machine
const unsigned int engine_id = 1;

// Déclaration du tic d'unicité de la requête
unsigned int tic = 0;

//déclaration des variables de connexion au serveur du timestamp
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 3600;

// Déclaration du pin chargé de lire la valeur de la tension 
// de la partie commande de la machine
const int input_voltage_pin = 32;

// Déclaration des variables de valeur de la tension
int input_voltage = 0;
int mapped_voltage = 0;


// VARIABLE DESIGNANT SI LA MACHINE    //
// EST EN FONCTGIONNEMENT OU A L'ARRET //
bool engine_state = false;


// Déclaration des pins chargés d'indiquer à la led RGB ce qu'elle doit indiquer
const int red_led_output = 33;
const int green_led_output = 25;
const int blue_led_output = 26;



//////////////////////////
//                      //
//    Esp32HTTPClient   //
//                      //
//////////////////////////

void networkConnection() {
  
    Serial.println();
    Serial.println();
    Serial.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFiMulti.addAP("iPhone de Clement", "ABCD1234");
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

boolean checkConnectionWasEstablished() {
    if(connection_established == true)
      return true;
    else 
      return false;
}

String defineHeaderRequest() {
  String header = "";
  header += "token=";
  header += String(generateToken());
  header += "&tic=";
  header += String(tic);
  header += "&engine_id=";
  header += String(engine_id);
  header += "&is_on=";
  header += String(engine_state);

  return header;
}

void sendDataToServer(String server_request)
{

    HTTPClient http;

    String header;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(server_request); //HTTPS

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header
    // Specify content-type header
    http.addHeader("Content-Type", "text/plain");
    header = defineHeaderRequest();
    //header = "";
    int httpCode = http.POST(header);
    //int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0)
    {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK)
        {
            //String payload = http.getString();
            //Serial.println(payload);
            Serial.println("");
            Serial.println("Inclusion réussie");
            Serial.println(server_request);
            Serial.println(header);
            Serial.println("");
        }
    }
    else
    {
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
}



//////////////////////////
//                      //
//        HASHAGE       //
//                      //
//////////////////////////

String generateToken() {
  String key_string = "iotprojet";
  key_string += String(tic);
  //Serial.println(key_string);
  char key[key_string.length()+1];
  key_string.toCharArray(key, key_string.length()+1);
  //Serial.println(key);
  unsigned char* hash=MD5::make_hash(key);
  //generate the digest (hex encoding) of our hash
  char *md5str = MD5::make_digest(hash, 16);
  //print it on our serial monitor
  //Serial.println(md5str);
  String md5string = md5str;
  //Serial.println(md5string);
  //Give the Memory back to the System if you run the md5 Hash generation in a loop
  free(md5str);
  //free dynamically allocated 16 byte hash from make_hash()
  free(hash);

  return String(md5string);
}




//////////////////////////
//                      //
//    VOLTAGE READER    //
//                      //
//////////////////////////

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
  int new_mapped_luminosity = map(analogRead(input_voltage_pin), 0, 5000, 0, 100);
  if(new_mapped_luminosity > 50) {
    return true;
  } 
  else 
    return false;
}

void defineEngineState() {
  readVoltage();
  mapVoltage();
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
  defineEngineState();
  
  displayMappedVoltage();
  displayEngineState();
  Serial.println("");
}

bool checkChangeEngineState() {
  if(engine_state != determineEngineState()) {
    Serial.println("ENGINE STATE CHANGED");
    return true;
  }
  else 
    return false;
}

void displayChangeEngineState() {
  Serial.println("");
  Serial.print("Etat de la machine : ");
  if(determineEngineState() == true)
    Serial.println("HIGH");
  else 
    Serial.println("LOW");
  Serial.print("Etat de la machine au tour de boucle prec. : ");
  if(engine_state == true)
    Serial.println("HIGH");
  else 
    Serial.println("LOW");
  Serial.println("");
}



//////////////////////////
//                      //
//       Esp32Save      //
//                      //
//////////////////////////

void initSave() {
  if(!SPIFFS.begin(true))
  {
    Serial.println("Error : Initialisation Sauvegarde");
  }

  eraseSave("/local_save_data.txt");
}

void saveRequest(String file_name, String server_request) {
  
  File file_data = SPIFFS.open(file_name, FILE_APPEND);

  if(!file_data){
    Serial.println("Erreur lors de la lecture du document");
    return;
  }
  if(!file_data.println(server_request))
  {
    Serial.println("Erreur : Impossible d'écrire sur le fichier");
  }
  else {
    Serial.println("Enregistrement de la requête en local");
  }
 
  file_data.close();
}

void readSave(String file_name, String saved_requests_list[30], int* nb_requests) {
  File read_file = SPIFFS.open(file_name);

  int i = 0;

  char request[100];
    
  while(read_file.available())
  {
    int l = read_file.readBytesUntil('\n', request, sizeof(request));
    request[l-1] = 0; //-1 pour ne pas avoir d'espace vide à la fin de la chaîne
    //Serial.println(request);
    saved_requests_list[i] = String(request);
    ++i;
  }

  *nb_requests = i;
  
  read_file.close();
}

void displaySaveReadding(String saved_requests_list[30]) {
  for(uint8_t i=0; i<30; ++i) {
    Serial.println(saved_requests_list[i]);
  }
}

void eraseSave(String file_name) {
  SPIFFS.remove(file_name);
}

void sendSaveToServer(String saved_requests_list[30], int nb_requests) {
  for(uint8_t i=0; i<nb_requests; ++i) {
    sendDataToServer(saved_requests_list[i]);
    delay(50);
  }
}



//////////////////////////
//                      //
//        LED RGB       //
//                      //
//////////////////////////

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

void showEngineState() {
  if(engine_state == true)
    showEngineOn();
  else
    showEngineOff();
}

void showDefaultConnection() {
  digitalWrite(red_led_output, HIGH);
  digitalWrite(green_led_output, HIGH);
  digitalWrite(blue_led_output, LOW);
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


                                ///////////      SETUP       ///////////


void setup() {

  Serial.begin(9600);

  pinMode(input_voltage_pin, INPUT);

  pinMode(red_led_output, OUTPUT);
  pinMode(green_led_output, OUTPUT);
  pinMode(blue_led_output, OUTPUT);

  networkConnection();

  initSave();

}


                                ///////////       LOOP       ///////////

void loop() {

  displayChangeEngineState();

  if(checkConnectionAvailable()) {

    if(!checkConnectionWasEstablished()) {
      String saved_requests_list[30];
      int nb_requests = 0;
      readSave("/local_save_data.txt", saved_requests_list, &nb_requests);
      sendSaveToServer(saved_requests_list, nb_requests);
      eraseSave("/local_save_data.txt");
      showConnectionEstablished();
    }

    connection_established = true;

    if(checkChangeEngineState()) {

      // Déclaration de la chaîne de caractères à insérer dans l'url
      String server_request = "https://corner.soccer/iot/server.php";
    
      defineEngineState();
      
      sendDataToServer(server_request);

    }

    showEngineState();
  }
  
  else {

    connection_established = false;

    showDefaultConnection();

    Serial.println("Défaut de connexion !");
    
    if(checkChangeEngineState()) {

      // Déclaration de la chaîne de caractères à insérer dans l'url
      String server_request = "https://corner.soccer/iot/server.php";
    
      defineEngineState();
      
      saveRequest("/local_save_data.txt", server_request); 

    }
  }

  ++tic;

  delay(1000);
  
}
