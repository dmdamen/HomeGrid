//#define motion_sensor
//#define battery_powered

#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <algorithm>
#include "FS.h"
#include "mqtt.h"
#include "store.h"
#include "views.h"
#include "wifi.h"
//#include "platform.h"

Wifi*     myWifi     = Wifi::getInstance();
Store*    myConfig   = Store::getInstance();
Mqtt*     myMqtt     = Mqtt::getInstance();
//Platform* myPlatform = Platform::getInstance();

int powerIndicator = D1;
int motionIndicator = D2;
int motionSensor = D6;

int motionTimer = 0;

//Ticker flashOn;
//Ticker flashOff;
//Ticker motionTicker;

//void TurnPowerIndicatorOn() {
//  digitalWrite(powerIndicator, HIGH);
//  flashOff.attach(0.06, TurnPowerIndicatorOff);
//}
//void TurnPowerIndicatorOff() {
//  digitalWrite(powerIndicator, LOW);
//  flashOff.detach();
//}

//ICACHE_RAM_ATTR void detectMovement() {
//  digitalWrite(motionIndicator, HIGH);
// myMqtt->publish("homegrid/km123/motion", "1");
//  Serial.println("motion");
//  motionTicker.attach(1, countdownMotionTimer);
//  motionTimer = 300;
//}

//void countdownMotionTimer() {
//  if (motionTimer > 0) {
//    bool stillMotion = digitalRead(motionSensor);
//    if (!stillMotion) {
//      motionTimer--;
//    }
//  } else {
//    digitalWrite(motionIndicator, LOW);
//    myMqtt->publish("homegrid/km123/motion", "0");
//    motionTicker.detach();
//  }
//}

void setup() {

  Serial.begin(115200);
  delay(500);
  Serial.println("\nBooting device");

  boolean isConfigOk = true;

  if (myConfig == NULL) {
    Serial.println("Error initializing EEPROM"); 
    delay(2000); 
    ESP.restart();
  } else {
    Serial.println("EEPROM OK");
  }
    
  if(!myWifi->connect(myConfig->getWifiName(), myConfig->getWifiPass())) { 
    Serial.println("Failed to connect to WiFi"); 
    isConfigOk = false;
  } else {
    Serial.print("IP Address : ");
    Serial.println(myWifi->getLocalIp().c_str());
    Serial.print("MAX Address: ");
    Serial.println(myWifi->getMacAddress().c_str());
  }

  if (myConfig->getDeviceName() == "") {
    Serial.println("Device name not set"); 
    isConfigOk = false;
  } else {
    Serial.print("Device name: ");
    Serial.println(myConfig->getDeviceName().c_str());  
  }

  //if (!myMqtt->connect(myConfig->getMqttServerName(), myConfig->getMqttServerFingerprint(), myConfig->getMqttUser(), myConfig->getMqttPass())) {
  if (!myMqtt->connect(myConfig->getMqttServerName(), myConfig->getMqttUser(), myConfig->getMqttPass())) {
    Serial.println("Failed to connect to MQTT server"); 
    isConfigOk = false;
  } else {
    Serial.print("MQTT Server: ");
    Serial.println(myConfig->getMqttServerName().c_str());
  }
    
  if (isConfigOk) {
     Serial.println("Ready");   
  } else {
    doConfig();
  }

  myMqtt->subscribe("homegrid/command",       mqttCallback);
  myMqtt->subscribe("homegrid/hm123/command", mqttCallback);

//    pinMode(powerIndicator,  OUTPUT);
//  pinMode(motionIndicator, OUTPUT);
//  pinMode(motionSensor,  INPUT);

//  digitalWrite(powerIndicator, LOW);
//  digitalWrite(motionIndicator, LOW);

//  flashOn.attach(1.5, TurnPowerIndicatorOn);

//  attachInterrupt(digitalPinToInterrupt(motionSensor), detectMovement, RISING);
}

void loop() 
{
  ws_loop();
  myMqtt->loop();
}

void doConfig() {

  Serial.println("");
  Serial.println("Loading configuration routine");
  myWifi->startAP("HomeGrid", "homegrid");

  ws_setupRoutes();
  ws_start();

  Serial.println("");
  Serial.println("Connect to a network called 'HomeGrid' using password 'homegrid'");
  Serial.print("Point your browser to http://");
  Serial.println(myWifi->getSoftApIp().c_str());

}

void mqttCallback(std::string* payload)
{
  if (payload->compare("reboot") == 0) {ESP.restart();}
  if (payload->compare("announce") == 0) {publishAnnounce();}
}

void publishAnnounce() {
  std::string message = "{\"id\":\"" + myConfig->getDeviceName() + "\",\"mac\":\"" + myWifi->getMacAddress() + "\",\"ip\":\"" + myWifi->getLocalIp() + "\"}";
  Serial.println(message.c_str());
  myMqtt->publish("homegrid/announce",message);
}
