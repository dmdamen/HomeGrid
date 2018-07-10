#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "FS.h"
#include "mqtt.h"
#include "store.h"
#include "views.h"
#include "wifi.h"

void setup() {

  Serial.begin(115200);
  delay(500);
  Serial.println("Booting device");

  boolean isConfigOk = true;

  Store* myConfig = Store::getInstance();
  if (myConfig == NULL) {Serial.println("Error initializing EEPROM"); delay(2000); ESP.restart();}
  
  if (myConfig->getDeviceName() == "") { Serial.println("Device name not set"); isConfigOk = false;}

  Wifi*  myWifi = Wifi::getInstance();
  if(!myWifi->connect(myConfig->getWifiName(), myConfig->getWifiPass())) { Serial.println("Failed to connect to WiFi"); isConfigOk = false;}

  Mqtt* myMqtt = Mqtt::getInstance();
  if (!myMqtt->connect(myConfig->getMqttServerName(), myConfig->getMqttServerFingerprint(), myConfig->getMqttUser(), myConfig->getMqttPass())) {Serial.println("Failed to connect to MQTT server"); isConfigOk = false;}

  if (isConfigOk) 
  {
    // Print configuration
    Serial.print("Device name: ");
    Serial.println(myConfig->getDeviceName().c_str());
  
    Serial.print("IP Address : ");
    Serial.println(myWifi->getLocalIp().c_str());

    Serial.print("MQTT Server: ");
    Serial.println(myConfig->getMqttServerName().c_str());
    Serial.print("Ready");
    
  } else {
    
    doConfig();
  }
}

void loop() 
{
  ws_loop();
}

void doConfig() {

  Serial.println("");
  Serial.println("Loading configuration routine");
  Wifi* myWifi = Wifi::getInstance();
  myWifi->startAP("HomeGrid", "homegrid");

  ws_setupRoutes();
  ws_start();

  Serial.println("");
  Serial.println("Connect to a network called 'HomeGrid' using password 'homegrid'");
  Serial.print("Point your browser to http://");
  Serial.println(myWifi->getSoftApIp().c_str());

}


