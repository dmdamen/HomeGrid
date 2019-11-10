#ifndef PLATFORM_H
#define PLATFORM_H

class Platform {

  private:
    static Platform* instance();
    Platform();

    //int ActivityIndicatorPin;
    //void TurnActivityIndicatorOn();
    //void TurnActivityIndicatorOff();

  public:
    static Platform* getInstance();
    void setup(int);
    void loop();
    
};

#endif
