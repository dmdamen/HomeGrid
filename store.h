#ifndef STORE_H
#define STORE_H

#include <string>

class Store {

  private:
    static Store* instance;
    Store();
    std::string setValue(int, int, std::string);
    std::string getValue(int, int);

  public:
    static Store* getInstance();
    void erase();
    std::string getDeviceName();
    std::string setDeviceName(std::string);
    
    std::string getWifiName();
    std::string setWifiName(std::string);

    std::string getWifiPass();
    std::string setWifiPass(std::string);

    std::string getMqttUser();
    std::string setMqttUser(std::string);

    std::string getMqttPass();
    std::string setMqttPass(std::string);

    std::string getMqttServerName();
    std::string setMqttServerName(std::string);

    std::string getMqttServerFingerprint();
    std::string setMqttServerFingerprint(std::string);
};

#endif
