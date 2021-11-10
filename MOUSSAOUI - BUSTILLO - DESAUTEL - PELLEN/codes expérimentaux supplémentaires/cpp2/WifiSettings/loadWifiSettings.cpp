#include "WifiSettings.cpp"

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


std::vector<WifiSettings*> loadAllWifiNetworks()
{

    std::vector<WifiSettings*> wifi_list;

    std::ifstream file(".././networks_settings/networks_settings.txt"); //Ouverture d'un fichier en lecture

    if (file)
    {
        //Tout est prêt pour la lecture.

        std::string wifi_name, wifi_password, ip;
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
                wifi_list.push_back(new WifiSettings(wifi_name, wifi_password, stay_connected, ip, last_network));

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
        std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
        // Serial.println("ERREUR: Impossible d'ouvrir le fichier en lecture.");
    }

    return wifi_list;
}

WifiSettings findWifiNetwork(std::vector<WifiSettings*> wifi_networks, std::string wifi_name_input) {
    WifiSettings choosen_wifi_network;
    bool check_wifi_found = false;

    for(unsigned int i=0; i<wifi_networks.size(); ++i) {
        if(wifi_networks[i]->checkName(wifi_name_input)) {
            check_wifi_found = true;
            choosen_wifi_network = *wifi_networks[i];
        }
    }

    if(!check_wifi_found)
        throw std::invalid_argument("Nom de réseau incorrect");

    return choosen_wifi_network;
}

std::string ChooseWifiNetwork() {

    std::string wifi_name_input;

    std::cout << "Entrez le nom du reseau auquel vous souhaitez vous connecter :" << std::endl;
    std::cin >> wifi_name_input;

    return wifi_name_input;
}

std::string ChooseWifiNetworkInSerial() {

    std::string wifi_name_input;

    //Mettre le code Arduino pour entrer du texte dans le moniteur Serie

    return wifi_name_input;
}

WifiSettings loadWifiNetwork(std::string wifi_name_input) {

    WifiSettings wifi_network;

    std::vector<WifiSettings*> wifi_networks = loadAllWifiNetworks();

    if(wifi_networks.size() != 0) {

        try {
            wifi_network = findWifiNetwork(wifi_networks, wifi_name_input);
        }
        catch(const std::exception& e) {
            std::cout << e.what() << std::endl;
        }

    }
    else {
        std::cout << "Aucun reseau trouve" << std::endl;
        // Serial.println("Aucun réseau trouvé");
    }

    return wifi_network;
}
