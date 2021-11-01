void networkConnection(ESP8266WiFiMulti* WiFiMulti) {
    for (uint8_t t = 4; t > 0; t--) {
        Serial.printf("[SETUP] WAIT %d...\n", t);
        Serial.flush();
        delay(1000);
    }

    WiFi.mode(WIFI_STA);
    WiFiMulti->addAP("Bbox-22111971", "22111971");
}

boolean checkConnectionAvailable(ESP8266WiFiMulti* WiFiMulti) {
    // wait for WiFi connection
    if ((WiFiMulti->run() == WL_CONNECTED)) {
        return true;
    }
    else {
        return false;
    }
}

void sendDataToServer() {

    WiFiClient client;

    HTTPClient http;

    Serial.print("[HTTP] begin...\n");

    if (http.begin(client, "http://192.168.1.54/wifi/data.php")) {
        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }

}