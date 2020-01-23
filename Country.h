#ifndef COUNTRY_H
#define COUNTRY_H

#include <string> 
#include <vector>
#include <iostream>
#include "Land.cpp"

using std::endl;
using std::cout;

class Player;
class Country : public Land
{
private:  
   int numOfSoldiers;
   std::string owner, continent;

public: 
   struct PlayersInCountry
    {
        Player *playerOccupying;
        int numberArmies;
		  int numOfCities;
    };
   vector <PlayersInCountry> playersInCountry;

   void addPlayerInCountry(Player *playerOccupatingCountry, int numberOfArmies, int numCities);
   
   // constructors
   Country(){}
   Country(int id, string name, string continent);
   
   //getters
   int getNumOfSoldiers();

   std::string getOwner();

   std::string getContinent();

   //setters
   void setNumOfSoldiers(int soldiers);

   void setOwner(std::string player);

   void setContinent(std::string Continent);
      
   void displayInfo();

};
#endif