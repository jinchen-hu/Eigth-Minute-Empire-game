#include "Land.h"

Land::Land(){}

Land::Land(int id, string name){
    ID = id;
    this->name = name;
}

int Land::getID(){
    return ID;
}

void Land::setID(int id){
    ID= id;
}

std::string Land::getName(){
    return name;
}

void Land::setName(std::string country){
    name = country;
}