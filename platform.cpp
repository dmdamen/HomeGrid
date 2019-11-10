#include "platform.h"

Platform* Platform::instance = 0;

Platform* Platform::getInstance() {
  if (instance == 0)
  {
    instance = new Platform();
  }
  return instance;
}

Platform::Platform() {}

//void Platform::TurnActivityIndicatorOn() {
  //digitalWrite(ActivityIndicatorPin, HIGH);
  //flashOff.attach(0.06, TurnPowerIndicatorOff);
//}
//void Platform::TurnActivityIndicatorOff() {
  //digitalWrite(ActivityIndicatorPin, LOW);
  //flashOff.detach();
//}

//void Platform::setup(int activityIndicatorPin) {
  //ActivityIndicatorPin = activityIndicatorPin;
//}

//void Platform::loop() {
  
//}
