void networkConnection(WiFiMulti *WiFiMulti) 
{
    USE_SERIAL.println();
    USE_SERIAL.println();
    USE_SERIAL.println();

    for (uint8_t t = 4; t > 0; t--)
    {
        USE_SERIAL.printf("[SETUP] WAIT %d...\n", t);
        USE_SERIAL.flush();
        delay(1000);
    }

    wifiMulti.addAP("SFR-75e0", "QJDXPVQLQDU4");
}

boolean checkConnectionAvailable(WiFiMulti *WiFiMulti)
{
    // wait for WiFi connection
    if ((WiFiMulti->run() == WL_CONNECTED))
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