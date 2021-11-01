#ifndef WifiSettings_H
#define WifiSettings_H

#include <fstream>
#include <vector>

class WifiSettings
{
    private:
        String _name;
        String _password;
        boolean _stay_connected;
        String _ip;
        boolean _last_network;

    public:
        WifiSettings(String name, 
                    String password, 
                    boolean stay_connected, 
                    String ip,
                    boolean last_network);
        
        // void saveWifi();
};

///////////////   FUNCTIONS ///////

// WifiSettings loadWifiNetwork() {
void loadWifiNetwork()
{

    std::ifstream file{".././networks_settings/networks_settings.txt"}; //Ouverture d'un fichier en lecture

    if (file)
    {
        //Tout est prêt pour la lecture.

        std::vector<WifiSettings*> wifi_list();

        String wifi_name, wifi_password, ip;
        boolean stay_connected, last_network;

        int config_lecture_level = 0;

        char a;

        Serial.println("TEST");

        while (file.get(a))
        {

            // a = file.get(a);

            Serial.print("lettre  ");
            Serial.print(a);

            // if (a == ';')
            // {
            //     config_lecture_level++;
            // }
            // else if (
            //     (a >= 'a' && a <= 'z') ||
            //     (a >= 'A' && a <= 'Z') ||
            //     (a >= '0' && a <= '9') || a == '-' || a == '_')
            // {

            //     switch (config_lecture_level)
            //     {
            //     case '0':
            //         wifi_name += a;
            //     case '1':
            //         wifi_password += a;
            //     case '2':
            //         stay_connected = parseBool(a);
            //     case '3':
            //         ip += a;
            //     case '4':
            //         last_network = parseBool(a);
            //     }
            // }
            // else
            // {
            // }

            // wifi_list.push_back(
            //     new WifiSettings(wifi_name,
            //                      wifi_password,
            //                      stay_connected,
            //                      ip,
            //                      last_network));
        }
    }
    else
    {
        // cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
        Serial.println("ERREUR: Impossible d'ouvrir le fichier en lecture.");
    }
}

#endif

