#include "WifiSettings.h"

#include <Vector.h>

bool parseBool(char a) {
    if(a == '0') {
        return false;
    }
    else if(a == '1') {
        return true;
    }
    else {
        return false;
    }
}

Vector<WifiSettings*> loadAllWifiNetworks()
{

    Vector<WifiSettings*> wifi_list;

    std::ifstream file(".././networks_settings/networks_settings.txt"); //Ouverture d'un fichier en lecture

    if (file)
    {
        //Tout est pr�t pour la lecture.

        String wifi_name, wifi_password, ip;
        bool stay_connected, last_network;

        const int WIFI_NAME_LECTURE_LEVEL = 0;
        const int WIFI_PASSWORD_LECTURE_LEVEL = 1;
        const int STAY_CONNECTED_LECTURE_LEVEL = 2;
        const int IP_LECTURE_LEVEL = 3;
        const int LAST_NETWORK_LECTURE_LEVEL = 4;
        const int END_LINE_LECTURE_LEVEL = 5;

        int config_lecture_level = 0;

        char a;

        while (file.get(a))
        {

            if (a == ';')
            {
                config_lecture_level++;
            }
            else if (
                (a >= 'a' && a <= 'z') ||
                (a >= 'A' && a <= 'Z') ||
                (a >= '0' && a <= '9') || a == '-' || a == '_')
            {

                switch (config_lecture_level)
                {
                    case WIFI_NAME_LECTURE_LEVEL:
                        wifi_name += a;
                        break;
                    case WIFI_PASSWORD_LECTURE_LEVEL:
                        wifi_password += a;
                        break;
                    case STAY_CONNECTED_LECTURE_LEVEL:
                        stay_connected = parseBool(a);
                        break;
                    case IP_LECTURE_LEVEL:
                        ip += a;
                    case LAST_NETWORK_LECTURE_LEVEL:
                        last_network = parseBool(a);
                        break;

                    default:
                        break;
                }
            }
            else
            {
            }

            if(config_lecture_level == END_LINE_LECTURE_LEVEL) {
                WifiSettings wifi_settings(wifi_name, wifi_password, stay_connected, ip, last_network);
                wifi_list.push_back(&wifi_settings);

                wifi_name = "";
                wifi_password = "";
                stay_connected = 0;
                ip = "";
                last_network = 0;


                config_lecture_level = WIFI_NAME_LECTURE_LEVEL;
            }

        }

    }
    else
    {
        // std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
        Serial.println("ERREUR: Impossible d'ouvrir le fichier en lecture.");
    }

    return wifi_list;
}

WifiSettings findWifiNetwork(Vector<WifiSettings*> wifi_networks, String wifi_name_input) {
    WifiSettings choosen_wifi_network;
    bool check_wifi_found = false;

    for(unsigned int i=0; i<wifi_networks.size(); ++i) {
        if(wifi_networks[i]->checkName(wifi_name_input)) {
            check_wifi_found = true;
            choosen_wifi_network = *(wifi_networks[i]);
        }
    }

    return choosen_wifi_network;
}

String ChooseWifiNetwork() {

    String wifi_name_input;

    // std::cout << "Entrez le nom du reseau auquel vous souhaitez vous connecter :" << std::endl;
    // std::cin >> wifi_name_input;

    return wifi_name_input;
}

String ChooseWifiNetworkInSerial() {

    String wifi_name_input;

    Serial.println("Entrez le nom du reseau auquel vous souhaitez vous connecter :");
    if(Serial.available() > 0) {
        wifi_name_input = Serial.read();
    }

    return wifi_name_input;
}

WifiSettings loadWifiNetwork(String wifi_name_input) {

    WifiSettings wifi_network;

    Vector<WifiSettings*> wifi_networks = loadAllWifiNetworks();

    if(wifi_networks.size() != 0) {

        wifi_network = findWifiNetwork(wifi_networks, wifi_name_input);

        // ATTENTION : PAS DE GESTION EN CAS DE MAUVAISE SAISIE

    }
    else {
        // std::cout << "Aucun reseau trouve" << std::endl;
        Serial.println("Aucun reseau trouve");
    }

    return wifi_network;
}
