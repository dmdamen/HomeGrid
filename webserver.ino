// I'd prefer a wrapper of some sort around he webserver 
// but I can't seem to get it to work the way I want it 
// to work. So, taking the easy way out :)

#include <ESP8266WebServer.h>
#include "views.h"

ESP8266WebServer ws(80);

bool webServerActive = false;

void ws_setupRoutes()
{
  ws.on("/", []() {
    Views* vw = Views::getInstance();
    Store* configStore = Store::getInstance();
    Wifi* wifi = Wifi::getInstance();
    
    std::string content = vw->configPage(configStore->getDeviceName(), wifi->getNetworks(), configStore->getWifiName(), configStore->getWifiPass(), configStore->getMqttServerName(), configStore->getMqttServerFingerprint(), configStore->getMqttUser(), configStore->getMqttPass());
   
    ws.send(200, "text/html", content.c_str());
  });

  ws.on("/set", []() {
    Store* configStore = Store::getInstance();

    configStore->setDeviceName(ws.arg("name").c_str());
    configStore->setWifiName(ws.arg("network").c_str());
    configStore->setWifiPass(ws.arg("pass").c_str());
    configStore->setMqttUser(ws.arg("mqtt_user").c_str());
    configStore->setMqttPass(ws.arg("mqtt_pass").c_str());
    configStore->setMqttServerName(ws.arg("mqtt_server").c_str());
    //configStore->setMqttServerFingerprint(ws.arg("mqtt_fingerprint").c_str());

  Serial.println();
    
    Views* vw = Views::getInstance();
    std::string content = vw->rebootPage();
    ws.send(200, "text/html", content.c_str());

    delay(2000);
    
    ESP.restart();    
  });

  ws.on("/reset" , []() {
    Store* configStore = Store::getInstance();
    configStore->erase();

    Views* vw = Views::getInstance();
    std::string content = vw->rebootPage();
    ws.send(200, "text/html", content.c_str());
    
    delay(2000);
    
    ESP.restart();
  });
}

void ws_loop()
{
  if (webServerActive) {
    ws.handleClient();
  } 
}

void ws_start()
{
  ws.begin();
  webServerActive = true;
}
