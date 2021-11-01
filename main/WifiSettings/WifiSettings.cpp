#include "WifiSettings.h"

WifiSettings::WifiSettings(String name, String password, boolean stay_connected, String ip, boolean last_network) {
    _name = name;
    _password = password;
    _stay_connected = stay_connected;
    _ip = ip;
    _last_network = last_network;
}
