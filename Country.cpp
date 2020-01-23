#include <string> 
#include <vector>
#include <iostream>
#include "Country.h"

using std::endl;
using std::cout;

void Country::addPlayerInCountry(Player *playerOccupatingCountry, int numberOfArmies, int numCities)
{
    PlayersInCountry newPlayerInCountry = PlayersInCountry();
    newPlayerInCountry.numberArmies = numberOfArmies;
    newPlayerInCountry.numOfCities = numCities;
    newPlayerInCountry.playerOccupying = playerOccupatingCountry;
    // add it to vector
    playersInCountry.push_back(newPlayerInCountry);
}

Country::Country(int id, string name, string continentName) : Land(id,name),continent(continentName)
{}

int Country::getNumOfSoldiers(){
    return numOfSoldiers;
}

std::string Country::getOwner(){
    return owner;
}
std::string Country::getContinent(){
    return continent;
}

//setters
void Country::setNumOfSoldiers(int soldiers){
    numOfSoldiers = soldiers;
}

void Country::setOwner(std::string player){
    owner = player;
}

void Country::setContinent(std::string continent) {
    this->continent = continent;
}
    
void Country::displayInfo()
{
    cout<< "\nPROPERTIES OF SELECTED TERRITORY  " << "\n"; 
    cout<< "Owner of Territory: " << getOwner() << "\n"; 
    cout<< "Country name: " << getName() << "\n"; 
    cout<< "Country ID: " << getID() << "\n"; 
    cout<< "Country Contenent: " << getContinent() << "\n"; 
    cout<< "Size Of Army: " << getNumOfSoldiers() << "\n"; 
}    

