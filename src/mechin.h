#include <math.h> 
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <curl/curl.h>
#include "position.h"
#ifndef MACHININ_H
#define MACHININ_H
class Machin{
private:
    std::string name;
    Position MachinPosion;
    bool status;
public:
    Machin(bool stat,Position maPosition,std::string name) : name(name),MachinPosion(maPosition),status(stat){}
    std::string get_name (){
        return name;
    };
    const Position& get_Position() const{
        return MachinPosion;
    };
    const bool& get_status()const{
        return status;
    };
    // ~Machin();
};
#endif 