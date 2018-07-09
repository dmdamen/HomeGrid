#include "store.h"
#include "wifi.h"

Wifi* Wifi::instance = 0;

Wifi* Wifi::getInstance()
{
  if (instance == 0)
  {
    WiFi.mode(WIFI_STA);
    instance = new Wifi();
    instance->scanAvailableNetworks();
  }
  return instance;
}

Wifi::Wifi() {}

boolean Wifi::connect(std::string Ssid, std::string password)
{
  bool IsConnected = false;
  WiFi.begin(Ssid.c_str(), password.c_str());

  int c = 0;
  while ( c < 20 ) {
    if (WiFi.status() == WL_CONNECTED) {
      IsConnected = true;
      break;
    }
    delay(500);
    c++;
  }
  return IsConnected;
}

void Wifi::scanAvailableNetworks()
{
  WiFi.disconnect();
  delay(100);

  int n = WiFi.scanNetworks();
  
  for (int i = 0; i < n; ++i)
  {
    delay(10);
    std::string newNetwork = WiFi.SSID(i).c_str();
    bool DoesListAlreadyContainNetwork = false;
    for (std::string network : availableNetworks) {
      if (network == newNetwork) {
        DoesListAlreadyContainNetwork = true;
      }
    }
    if (!DoesListAlreadyContainNetwork) {
      this->availableNetworks.push_back(newNetwork);
    }
  }
}

boolean Wifi::startAP(std::string ssid, std::string password)
{
  WiFi.mode(WIFI_AP);
  return WiFi.softAP(ssid.c_str(), password.c_str()); 
}

std::string Wifi::getLocalIp()
{
  return WiFi.localIP().toString().c_str();
}

std::string Wifi::getSoftApIp()
{
  return WiFi.softAPIP().toString().c_str();
}

std::vector <std::string> Wifi::getNetworks()
{
  return availableNetworks;
}

