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

Mqtt::Mqtt() {
  myStore = Store::getInstance();
  callbackItems = {};
}

std::vector<callbackItem>* Mqtt::callbackItems = 0;
std::vector<callbackItem>* Mqtt::getCallbackItems() {
  if (callbackItems ==0)
  {
    callbackItems = new std::vector<callbackItem>();
  }
  return callbackItems;
}

void Mqtt::subscribe(std::string topic, void (*Callback)(std::string*)) {
   callbackItem item;
   item.topic = topic;
   item.callback = Callback;
   Mqtt::getCallbackItems()->push_back(item);
   mqttClient.subscribe(topic.c_str());
}

void Mqtt::publish(std::string topic, std::string message) {
  mqttClient.publish(topic.c_str(), message.c_str());
}

//bool Mqtt::connect(std::string serverName, std::string fingerPrint, std::string username, std::string password) {
bool Mqtt::connect(std::string serverName, std::string username, std::string password) {
  bool returnValue = false;

  //mqttClient = PubSubClient(serverName.c_str(), 8883, Mqtt::mqtt_callback, secureClient);
  mqttClient = PubSubClient(serverName.c_str(), 1883, Mqtt::mqttCallback, Client);
  
  if (mqttClient.connect(myStore->getDeviceName().c_str(), username.c_str(), password.c_str(), getWillTopic().c_str(), 0, false, getWillMsg().c_str())) {

    mqttClient.publish(Mqtt::getBirthTopic().c_str(), Mqtt::getBirthMsg().c_str());
    //if (secureClient.verify(fingerPrint.c_str(), serverName.c_str())) {
      returnValue = true;
    //}
  }    
  return returnValue;
}

bool Mqtt::reconnect() {
  
}

void Mqtt::loop() {
  mqttClient.loop();
}

void Mqtt::mqttCallback(char* topic, byte* payload, unsigned int length)
{  
  std::string test = "";
  for (int i=0;i<length;i++) {
    test += payload[i];
  }
  for (int i=0; i < Mqtt::getCallbackItems()->size(); i++) {
    
    callbackItem cbi = Mqtt::getCallbackItems()->at(i);    
    if (cbi.topic.compare(topic) == 0) {
      cbi.callback(&test);  
    }
  }
}

std::string Mqtt::getWillTopic() {
  std::string topic = "homegrid/" + myStore->getDeviceName() + "/online";
  return topic;
}
std::string Mqtt::getWillMsg(){
  return "false";
}
std::string Mqtt::getBirthTopic(){
  std::string topic = "homegrid/" + myStore->getDeviceName() + "/online";
  return topic;
}
std::string Mqtt::getBirthMsg(){
  return "true";
}
