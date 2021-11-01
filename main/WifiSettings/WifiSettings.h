#ifndef WifiSettings_H
#define WifiSettings_H

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
                    String _ip,
                    boolean last_network);
        
        void saveWifi();
}

WifiSettings determinWifiNetwork() {

    ifstream file("../networks_settings/networks_settings.txt");  //Ouverture d'un fichier en lecture

    if(file)
    {
        //Tout est prêt pour la lecture.

        char a;

        while(get(a, file)) {
            file.get(a)
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }
} 

