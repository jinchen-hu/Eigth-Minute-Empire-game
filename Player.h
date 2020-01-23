#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "CardsFactory.h"
#include "Country.h"
#include "PlayerStrategies.h"
#include "GameObservers.h"

#include "Map.h"
using namespace std;

class BiddingRoom;
class Deck;
class Card;
class PlayerStrategy;
class GreedyPlayer;
class ModeratePlayer;

class Player : public Observable
{   
    public:

    enum StrategyType
    {
        INTERACTIVE, GREEDY, MODERATE
    };

    BiddingRoom *playerBiddingRoom;
    vector <Card*> playerHand;
    
    struct OccupiedCountry
    {
        Country *country;
        int numberArmies;
		int numberCities;
    };
    vector <OccupiedCountry> countriesOccupied;

    // default constructor
    Player();
    // argument constructor
    Player(string name, string armycolor, int age, int tokens);
    //destructor
    ~Player();
    //getter
    string getPlayerName();
    int getPlayerAge();
    int getNumOfArmies();
    int getNumOfCities();
    int getNumOfTokens();
    string getArmyColor();
    int getNumOfCards();
    //setter
    void setNumOfArmies(int numArmies);

    void setPlayerName(string name);

    void setPlayerAge(int age);
    
    void setNumOfTkens(int tokens);
    
    void setNumOfCities(int cities);
    
    void setArmyColor(string color);

    void addCountryOccupied(Country * country, int numOfArmies, int numOfCities);
    
    void setStrategy(int strat);

    bool isComp();
    //fuction
    /*
     Check if the player has enough coins before paying
     */
    void payCoins(int coin);
    Card* chooseExchange(Deck * deck);

    string chooseExchange_new(Deck * deck);

    // added this to pass players, to know how many players and how many cards each player has, in order to determine END
    string chooseExchange_withPlayers(Deck * deck, vector <Player *> players);

    string chooseExchange_new2(Deck * deck);
    /*
     1. which cities can place on
     2. choose a city -- c
     3. add the army -- army
     4. repeat till place all the armies
     */
    
    //void PlaceNewArmies(int army, Country *c);
    void placeNewArmies(Graph *graph);
    /*
    1. choose one of armies
    2. which regions can the army move to
    3. move to the destination
     */
    
    void moveArmies(Graph *map, bool byWater);

    vector<Country> *getAdjacencyCountries(string cName, Graph *map, bool byWater);
    //c1--the country that the player moves the army out
    //c2--the country that the player moves the army in
    //void moveBetweenCountrise(Country *c1, Country *c2);
    /*
    1. choose one of armies
    2. which regions can the army move to
    3. move to the destination
     */
    void moveOverLand(Graph *map);
    void moveOverLandAndWater(Graph *map);
    /*
     1. which coutry can player build a city
     2. choose a country
     3. build city
     */
    void buildCity(Graph *map);

    /*
     1. choose a coutry
     2. show the army name
     3. choose an army u wanna destroy
     */
    void destroyArmy(Graph *map, vector<Player *> players);
    
    // void destroy(Country *c);

	int computeScore(vector<Player>, Graph *);
    // OVERRIDE
    int computeScore2(vector<Player *> players, Graph *map);

    //method that prints the details of the player
    void print();
    
    bool isControlCountry(Country *);

    //returns number of countries that the player controls
    int getNumOfControlledCountries();

    //lets user choose which card to exchange against tokens
    //void chooseExchange(Deck *);
    
    void printCountries();

    bool ignore();

    void play(Card * card, Graph * graph, vector<Player*> players);
    //
    private:
    //delcare the palyer's name
    string playerName;
    //declare the player age
    int playerAge;
    //3 armies at the beginning
    int numOfArmies;
    string armyColor;
    
    //declare the number of cities, and defualt value is 3
    int numOfCities;
    
    //declare the number of tokens
    int numOfTokens;
    //the number of card
    int numOfCards;
    //number of cubes
    int numOfCubues;
    //number of disks
    int numOfDisks;

    PlayerStrategy * strategy;

    int getPointsFromGoods();    
};

#endif