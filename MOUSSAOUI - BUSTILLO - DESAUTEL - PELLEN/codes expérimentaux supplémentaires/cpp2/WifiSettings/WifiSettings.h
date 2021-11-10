#ifndef WIFISETTINGS_H_INCLUDED
#define WIFISETTINGS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>

class WifiSettings
{
    private:
        std::string _name;
        std::string _password;
        bool _stay_connected;
        std::string _ip;
        bool _last_network;

    public:
        WifiSettings();

        WifiSettings(std::string name,
                    std::string password,
                    bool stay_connected,
                    std::string ip,
                    bool last_network);

        ~WifiSettings();

        void displayWifiSettings();

        void displayWifiSettingsInSerial();

        bool checkName(std::string wifi_name_input);

        // void saveWifi();
};

#endif // WIFISETTINGS_H_INCLUDED
