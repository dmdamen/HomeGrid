#include "mqtt.h"

Mqtt* Mqtt::instance = 0;

Mqtt* Mqtt::getInstance()
{
  if (instance == 0)
  {
    instance = new Mqtt();
  }
  return instance;
}

Mqtt::Mqtt() {}

bool Mqtt::connect(std::string serverName, std::string fingerPrint, std::string username, std::string password)
{
  bool returnValue = false;
  Store* myStore = Store::getInstance();
  
  mqttClient = PubSubClient(serverName.c_str(), 8883, Mqtt::mqtt_callback, secureClient);
    
  if (mqttClient.connect(myStore->getDeviceName().c_str(), username.c_str(), password.c_str(), "willTopic", 0, false, "willMsg")) {

    if (secureClient.verify(fingerPrint.c_str(), serverName.c_str())) {
      returnValue = true;
    }
  }
    
  return returnValue;
}

void Mqtt::mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  
}
