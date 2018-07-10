#include "store.h"
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include "FS.h"
#include "views.h"
#include "wifi.h"

void setup() {

  Serial.begin(115200);
  Serial.println("Booting");

  boolean isConfigOk = true;

  Store* myConfig = Store::getInstance();
  if (myConfig == NULL) {Serial.println("Error initializing EEPROM"); delay(2000); ESP.restart();}
  
  if (myConfig->getDeviceName() == "") { Serial.println("Device name not set"); isConfigOk = false;}

  Wifi*  myWifi = Wifi::getInstance();
  if(!myWifi->connect(myConfig->getWifiName(), myConfig->getWifiPass())) { Serial.println("Failed to connect to WiFi"); isConfigOk = false;}

  if (isConfigOk) 
  {
    // Print configuration
    Serial.print("Device name: ");
    Serial.println(myConfig->getDeviceName().c_str());
  
    Serial.print("IP Address:  ");
    Serial.println(myWifi->getLocalIp().c_str());
  } else {
    
    doConfig();
  }
}

void loop() 
{
  ws_loop();
}

void doConfig() {

  Serial.println("Loading configuration routine");
  Wifi* myWifi = Wifi::getInstance();
  myWifi->startAP("HomeGrid", "homegrid");

  ws_setupRoutes();
  ws_start();
  
  Serial.println("Connect to a network called 'HomeGrid' using password 'homegrid'");
  Serial.print("Point your browser to http://");
  Serial.println(myWifi->getSoftApIp().c_str());

}


