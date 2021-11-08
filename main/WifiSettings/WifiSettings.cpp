#include "WifiSettings.h"

// WifiSettings::WifiSettings(String name, String password, bool stay_connected, String ip, bool last_network) {
//     _name = name;
//     _password = password;
//     _stay_connected = stay_connected;
//     _ip = ip;
//     _last_network = last_network;
// }

// WifiSettings::~WifiSettings() {

// }

// void WifiSettings::displayWifiSettings() {
//     // std::cout << std::endl;
//     // std::cout << std::endl;
//     // std::cout << "Nom du reseau : " << _name << std::endl;
//     // std::cout << "Mot de passe du reseau : " << _password << std::endl;
//     // std::cout << "Connexion automatique ? " << _stay_connected << std::endl;
//     // std::cout << "IP du reseau : " << _ip << std::endl;
//     // std::cout << "Dernier reseau utilise ? " << _last_network << std::endl;
//     // std::cout << std::endl;
// }

// void WifiSettings::displayWifiSettingsInSerial() {
//     Serial.println();
//     Serial.println();
//     Serial.print("Nom du reseau : "); Serial.println(this->_name);
//     Serial.print("Mot de passe du reseau : "); Serial.println(this->_password);
//     Serial.print("Connexion automatique ? "); Serial.println(this->_stay_connected);
//     Serial.print("IP du reseau : "); Serial.println(this->_ip);
//     Serial.print("Dernier reseau utilise ? "); Serial.println(this->_name);
// }

// bool WifiSettings::checkName(String wifi_name_input) {

//     if((this->_name).compareTo(wifi_name_input) == 0) {
//         return true;
//     }
//     else {
//         return false;
//     }
// }
