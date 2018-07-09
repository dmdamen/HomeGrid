#include "store.h"
#include <EEPROM.h>
#include "FS.h"
#include <string>

#define EEPROM_SIZE 512
#define EEPROM_DEVICE_NAME_OFFSET 0
#define EEPROM_DEVICE_NAME_LENGTH 12
#define EERPOM_WIFI_NAME_OFFSET 12
#define EEPROM_WIFI_NAME_LENGTH 32
#define EEPROM_WIFI_PASS_OFFSET 44
#define EEPROM_WIFI_PASS_LENGTH 64
#define EEPROM_MQTT_SERVER_NAME_OFFSET 108
#define EEPROM_MQTT_SERVER_NAME_LENGTH 256
#define EEPROM_MQTT_SERVER_FINGERPRINT_OFFSET 364
#define EEPROM_MQTT_SERVER_FINGERPRINT_LENGTH 40
#define EEPROM_MQTT_USER_OFFSET 404
#define EEPROM_MQTT_USER_LENGTH 32
#define EEPROM_MQTT_PASS_OFFSET 436
#define EEPROM_MQTT_PASS_LENGTH 32

Store* Store::instance = 0;

Store* Store::getInstance()
{
  if (instance == 0)
  {
    EEPROM.begin(EEPROM_SIZE);
  
    if (SPIFFS.begin()) {
      instance = new Store();  
    } else {
      instance = NULL;
    }
  }
  return instance;
}

Store::Store() {}

void Store::erase() 
{
  for (int i = 0; i < EEPROM_SIZE; ++i) { EEPROM.write(i, 0); }
  EEPROM.commit();
}

std::string Store::setValue(int valueOffset, int valueLength, std::string value)
{
  std::string realNewValue = "";
  
  for (int i = 0; i < valueLength; ++i)
  {
    if (i < value.length()) {
      realNewValue += value[i];
      EEPROM.write(valueOffset + i, value[i]);
    }
    else
    {
      EEPROM.write(valueOffset + i, '\0');
    }
  }
  EEPROM.commit();
  return realNewValue;
}

std::string Store::getValue(int valueOffset, int valueLength)
{
  std::string value = "";
  for (int i = 0; i < valueLength; ++i)
  {
    char c = char(EEPROM.read(valueOffset + i));
    if (c != '\0') {value += c;}
  }
  return value;
}

std::string Store::getDeviceName()
{
  return getValue(EEPROM_DEVICE_NAME_OFFSET, EEPROM_DEVICE_NAME_LENGTH);
}

std::string Store::setDeviceName(std::string newName)
{
  return setValue(EEPROM_DEVICE_NAME_OFFSET, EEPROM_DEVICE_NAME_LENGTH, newName);
}

std::string Store::getWifiName()
{
  return getValue(EERPOM_WIFI_NAME_OFFSET, EEPROM_WIFI_NAME_LENGTH);
}

std::string Store::setWifiName(std::string newName)
{
  return setValue(EERPOM_WIFI_NAME_OFFSET, EEPROM_WIFI_NAME_LENGTH, newName);
}

std::string Store::getWifiPass()
{
  return getValue(EEPROM_WIFI_PASS_OFFSET, EEPROM_WIFI_PASS_LENGTH);
}

std::string Store::setWifiPass(std::string newPass)
{
  return setValue(EEPROM_WIFI_PASS_OFFSET, EEPROM_WIFI_PASS_LENGTH, newPass);
}

std::string Store::getMqttUser()
{
  return getValue(EEPROM_MQTT_USER_OFFSET, EEPROM_MQTT_USER_LENGTH);
}

std::string Store::setMqttUser(std::string newUser)
{
  return setValue(EEPROM_MQTT_USER_OFFSET, EEPROM_MQTT_USER_LENGTH, newUser);
}

std::string Store::getMqttPass()
{
  return getValue(EEPROM_MQTT_PASS_OFFSET, EEPROM_MQTT_PASS_LENGTH);
}

std::string Store::setMqttPass(std::string newPass)
{
  return setValue(EEPROM_MQTT_PASS_OFFSET, EEPROM_MQTT_PASS_LENGTH, newPass);
}

std::string Store::getMqttServerName()
{
  return getValue(EEPROM_MQTT_SERVER_NAME_OFFSET, EEPROM_MQTT_SERVER_NAME_LENGTH);
}

std::string Store::setMqttServerName(std::string newName)
{
  return setValue(EEPROM_MQTT_SERVER_NAME_OFFSET, EEPROM_MQTT_SERVER_NAME_LENGTH, newName);
}

std::string Store::getMqttServerFingerprint()
{
  std::string value = getValue(EEPROM_MQTT_SERVER_FINGERPRINT_OFFSET, EEPROM_MQTT_SERVER_FINGERPRINT_LENGTH);
  std::string newValue = "";

  //Add stripped colon characters back into the string
  for (int i=0; i < value.length(); i++)
  {
    newValue += value[i];
    if ( (((i+1) % 2) == 0) && ((i+1) < value.length())) {newValue += ':';}
  }
  
  return newValue;
}

std::string Store::setMqttServerFingerprint(std::string newFingerprint)
{
  // Strip colon characters to save space
  std::string minimizedFingerprint = "";
  
  for (int i=0; i < newFingerprint.length(); i++)
  {
    char c = newFingerprint[i];
    if (c != ':')
    {
      minimizedFingerprint += c;
    }
  }
  
  return setValue(EEPROM_MQTT_SERVER_FINGERPRINT_OFFSET, EEPROM_MQTT_SERVER_FINGERPRINT_LENGTH, minimizedFingerprint);
}





