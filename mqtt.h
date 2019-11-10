#ifndef MQTT_H
#define MQTT_H

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <vector>
#include "store.h"

struct callbackItem {
  std::string topic;
  void (*callback)(std::string*);
};

class Mqtt {

  private:
    static Mqtt* instance;
    Mqtt();

    Store* myStore;

    static std::vector<callbackItem>* callbackItems;
    
    //WiFiClientSecure secureClient;
    WiFiClient Client;
    PubSubClient mqttClient;

    //void (*callback)(std::string*);

    std::string getWillTopic();
    std::string getWillMsg();
    std::string getBirthTopic();
    std::string getBirthMsg();

    static void mqttCallback(char*, byte*, unsigned int);
    
  public:
    static Mqtt* getInstance();
    static std::vector<callbackItem>* getCallbackItems();
    void publish(std::string, std::string); 
    
    //bool connect(std::string, std::string, std::string, std::string);
    bool connect(std::string, std::string, std::string);
    bool reconnect();
    void subscribe(std::string, void (*)(std::string*));
    
    
    void loop();
};

#endif


/*


void loop() {
    mqttClient.loop();
}

void mqtt_reconnect() {
  
  while (!mqttClient.connected()) {
    
    Serial.print("Attempting secure MQTT connection to ");
    Serial.println(mqtt_server_fqdn);
    
    if (mqttClient.connect(mqtt_device_id, mqtt_username, mqtt_password, mqtt_willTopic, mqtt_willQoS, mqtt_willRetain, mqtt_willMessage)) {

  

      if (secureClient.verify(mqtt_server_certificate_fingerprint_sha1, mqtt_server_fqdn)) {
        
        Serial.println("MQTT server identity valid");
        Serial.println("Connection established");    
            
        mqttClient.subscribe("iot/sensors/light02/trigger");
        Serial.println("Subscribed to topic iot/sensors/light02/trigger");

        mqttClient.subscribe("iot/sensors/light02/ota");
        Serial.println("Subscribed to topic iot/sensors/light02/ota");

        mqttClient.subscribe("iot/sensors/light02/led");
        Serial.println("Subscribed to topic iot/sensors/light02/led");

        mqttClient.publish(mqtt_birthTopic, mqtt_birthMessage, mqtt_birthRetain);
        
      } else {
        
        mqttClient.disconnect();
        Serial.println("MQTT server identity invalid");
        Serial.println("Connection terminated");
        delay(5000);
      }
      
    } else {
      
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void publishValue() {
  char buf[4];
  sprintf(buf, "%d", CB.value);
  mqttClient.publish(mqtt_valueTopic, buf);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) {

  bool handled = false;

  if (strcmp(topic,"iot/sensors/light02/trigger") == 0) {
    CB.shouldPublish = true;
    handled = true;
  } 
  
  if (strcmp(topic,"iot/sensors/light02/led") == 0) {
    CB.shouldRestart = true;
    handled = true;
  }

  if (strcmp(topic, "iot/sensors/light02/ota") == 0){
    CB.enableOTA = true;
    handled = true;
  }
  
  if (handled == false) {
    Serial.print("Unhandled topic: ");
    Serial.println(topic);  
  }
}

  if (secureClient.connected() == 0)
     setup_wifi();
  
  if (!mqttClient.connected())
    mqtt_reconnect();

*/
   
