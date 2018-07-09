#ifndef WIFI_H
#define WIFI_H

#include <ESP8266WiFi.h>

class Wifi {

  private:
    static Wifi* instance;
    
    std::vector <std::string> availableNetworks;
    void scanAvailableNetworks();
    Wifi();

  public:
    static Wifi* getInstance();
    boolean connect(std::string, std::string);
    std::vector <std::string> getNetworks();
    boolean startAP(std::string, std::string);
    std::string getLocalIp();
    std::string getSoftApIp();
};

#endif
