#ifndef VIEWS_H
#define VIEWS_H

#include <string>
#include <vector>

class Views {

  private:
    static Views* instance;
    std::string style();
    Views();

  public:
    static Views* getInstance();
    std::string configPage(std::string, std::vector <std::string>, std::string, std::string);
    std::string rebootPage();

};

#endif
