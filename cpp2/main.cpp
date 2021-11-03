#include <iostream>

#include "WifiSettings/WifiSettings.h"

#include "WifiSettings/loadWifiSettings.cpp"

//using namespace std;

int main()
{
    WifiSettings wifi_network;

    wifi_network = loadWifiNetwork(ChooseWifiNetwork());
    wifi_network.displayWifiSettings();
    return 0;
}
