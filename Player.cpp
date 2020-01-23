#ifndef PLAYER_CPP
#define PLAYER_CPP
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Player.h"
#include "CardsFactory.h"
//#include "Map.cpp"
#include "PlayerStrategies.cpp"
#include "GameObservers.cpp"

using namespace std;

//constructors
Player::Player(){};

Player::Player(string name, string armycolor, int age, int tokens)
{
    strategy = new InteractivePlayer();
    playerName = name;     //new string(name);
    playerAge = age;       //new int(age);
    numOfTokens = tokens;  //new int(tokens);
    armyColor = armycolor; //new string(color);
    //Each player has 3 armies at the beginning of the game
    numOfArmies = 3; // new int(3);
    numOfCities = 0; //new int(0);
    numOfCards = 0;  //new int(0);
    numOfCubues = 0; //new int(0);
    numOfDisks = 0;  //new int(0);
}

//destructor
Player::~Player()
{
    //std::cout << "destructor called for Player" << endl;
    //delete playerBiddingRoom;
    /*
    delete playerName;
    delete playerAge;
    delete numOfTokens;
    delete armyColor;
    delete numOfArmies;
    delete numOfCities;
    delete numOfCubues;
    delete numOfCards;
    delete numOfDisks;
    */
}

//getter
inline string Player::getPlayerName()
{
    return playerName;
}
inline int Player::getPlayerAge()
{
    return playerAge;
}
inline int Player::getNumOfArmies()
{
    return numOfArmies;
}
inline int Player::getNumOfCities()
{
    return numOfCities;
}
inline int Player::getNumOfTokens()
{
    return numOfTokens;
}
inline string Player::getArmyColor()
{
    return armyColor;
}
inline int Player::getNumOfCards()
{
    return numOfCards;
}
//setter
inline void Player::setNumOfArmies(int numArmies)
{
    numOfArmies = numArmies;
}

inline void Player::setPlayerName(string name)
{
    playerName = name;
}

inline void Player::setPlayerAge(int age)
{
    playerAge = age;
}

inline void Player::setNumOfTkens(int tokens)
{
    numOfTokens = tokens;
}

inline void Player::setNumOfCities(int cities)
{
    numOfCities = cities;
}

inline void Player::setArmyColor(string color)
{
    armyColor = color;
}

void Player::setStrategy(int strategyChoice)
{
    //delete strategy;
    //strategy = NULL;

    if (strategyChoice == INTERACTIVE)
        strategy = new InteractivePlayer(this);
    if (strategyChoice == GREEDY)
        strategy = new GreedyPlayer(this);
    if (strategyChoice == MODERATE)
        strategy = new ModeratePlayer(this);
}

bool Player::isComp()
{

    if (typeid(*strategy) == typeid(GreedyPlayer) || typeid(*strategy) == typeid(ModeratePlayer))
    {
        return true;
    }
    return false;
}
//fuction
/*
Check if the player has enough coins before paying
*/
void Player::payCoins(int coin)
{

    if (numOfTokens - coin >= 0)
    {
        this->setNumOfTkens(this->getNumOfTokens() - coin);
    }
    else
    {
        cout << "Sorry, you do not have enough coin." << endl;
    }
}

Card *Player::chooseExchange(Deck *deck)
{
    Card *card = strategy->exchange(deck);
    string msg = "Player [" + this->getPlayerName() + "] took a card, he/she could " + card->getAction();
    //playerHand.push_back(card);
    numOfCards++;
    Notify2(msg);
    return card;
}

string Player::chooseExchange_new(Deck *deck)
{
    string action = strategy->chooseExchange(deck);
    string msg = "Player [" + this->getPlayerName() + "] took the " + action.at(1) + " card from the left, he/she would pay " + action.at(2) + " coin(s), and could " + action.at(0);
    Notify2(msg);
    return action;
}

string Player::chooseExchange_new2(Deck *deck)
{
    vector<string> action = strategy->chooseExchange2(deck);
    string msg = "Player [" + this->getPlayerName() + "] took the " + action.at(1) + " card from the left, he/she would pay " + action.at(2) + " coin(s), and could " + action.at(0);
    Notify2(msg);
    return action.at(0);
}

// added this to pass players, to know how many players and how many cards each player has, in order to determine END
string Player::chooseExchange_withPlayers(Deck *deck, vector<Player *> players)
{
    // 2 players - 13 cards (ENDS)
    // 3 players - 10 cards (ENDS)
    // 4 players - 8 cards (ENDS)
    // 5 players - 7 cards (ENDS)
    // Check number of players, and check if all players have the maximum number of cards (at same time)

    return strategy->chooseExchange(deck, players);
}

void Player::play(Card * card, Graph * graph, vector<Player*> players){
    strategy->play(card,graph,players,this);
}

/*
    1. which cities can place on
    2. choose a city
    3. add the army
    4. repeat till place all the armies

    You may place army only on the starting region or on a region where you have a city
*/
void Player::placeNewArmies(Graph *graph)
{
    // Observer: who is controlling country before placing army?
    // If a new player controls a country, Update()
    strategy->placeNewArmies(graph);
    string msg = "Player [" + this->getPlayerName() + "] place an army";
    Notify2(msg);
}

/*
1. choose one of armies
2. which regions can the army move to
3. move to the destination
*/
void Player::moveArmies(Graph *map, bool byWater)
{
    // Observer: who is controlling country before moving army?
    // If a new player controls a country, Update()

    strategy->moveArmies(map, byWater);
}

/*
1. check if there exists an army that the play could move out
2. which regions can the army move to
3. move to the destination
*/
void Player::moveOverLand(Graph *map)
{
    // Observer: who is controlling country before moving army?
    // done in: Player::moveArmies(map, byWater);
    string msg = "Player [" + this->getPlayerName() + "] moved an army";
    strategy->moveOverLand(map);
    Notify2(msg);
}
void Player::moveOverLandAndWater(Graph *map)
{
    // Observer: who is controlling country before moving army?
    // done in: Player::moveArmies(map, byWater);
    string msg = "Player [" + this->getPlayerName() + "] moved an army";
    strategy->moveOverLandAndWater(map);
    Notify2(msg);
}

//void Player::moveBetweenCountrise(Country *c1, Country *c2){}

/*
1. which coutry can player build a city
2. choose a country
3. build city
======= city can be built in the coutry where the player have arimies ======
*/
void Player::buildCity(Graph *map)
{
    strategy->buildCity(map);

    // NOTIFY Observer(s)
    string msg = "Player [" + this->getPlayerName() + "] built a city";
    Notify2(msg);
}

/*
1. choose a coutry
2. show the army name
3. choose an army u wanna destroy
======== if one of player' armies was destroyed by others,
======== their maximal number of armies will minus 1
*/
void Player::destroyArmy(Graph *map, vector<Player *> players)
{
    strategy->destroyArmy(map, players);

    // NOTIFY Observer(s)
    string msg = "Player [" + this->getPlayerName() + "] destroyed an army";
    Notify2(msg);
}

/*
* Helper functions
*/
int getNumOfCountriesInContinent(Player *player, vector<Country> *continent)
{
    int controlledCountriesInContinent = 0;
    for (int j = 0; j < continent->size(); j++)
    {
        if (player->isControlCountry(&continent->at(j)))
            controlledCountriesInContinent++;
    }
    return controlledCountriesInContinent;
}
vector<Country> *getCountriesFromContinents(string continent, Graph *map)
{
    vector<Country> *countries = new vector<Country>;
    for (int i = 0; i < map->V; i++)
    {
        if (map->arr[i].country->getContinent() == continent)
        {
            countries->push_back((*map->arr[i].country));
        }
    }
    return countries;
}

// int Player::getPointsFromGoods(){
//     map<string,int> goods;
//     for(int i = 0; i < playerHand.size(); i++){
//          if (std::find(goods.begin(), goods.end(), playerHand.at(i).getGood()) == goods.end())
//         {
//             // someName not in name, add it
//             goods.insert(pair<string,int>(playerHand.at(i).getGood(),0));
//         }
//         else{
//             goods[playerHand.at(i).getGood()]++;
//         }
//     }
// }
int Player::getNumOfControlledCountries()
{
    int numOfCountries = 0;
    for (int i = 0; i < countriesOccupied.size(); i++)
    {
        if (isControlCountry(countriesOccupied.at(i).country))
            numOfCountries++;
    }
    return numOfCountries;
}

int Player::computeScore(vector<Player> players, Graph *map)
{
    int score = 0;
    score += getNumOfControlledCountries();
    string continent;
    vector<string> continents;
    //1. Add each continent of player to hashmap
    for (int i = 0; i < countriesOccupied.size(); i++)
    {
        continent = countriesOccupied.at(i).country->getContinent();
        if (std::find(continents.begin(), continents.end(), continent) == continents.end())
        {
            // someName not in name, add it
            continents.push_back(continent);
        }
    }
    //2. For each continent in map, get all countries of continent
    int controlledCountriesInContinent = 0;
    bool controlContinent = true;
    vector<Country> *countriesInContinent;
    for (int i = 0; i < continents.size(); i++)
    {
        countriesInContinent = getCountriesFromContinents(continents.at(i), map);
        controlContinent = true;
        controlledCountriesInContinent = getNumOfCountriesInContinent(this, countriesInContinent);
        for (int j = 0; j < players.size(); j++)
        {
            if (controlledCountriesInContinent < getNumOfCountriesInContinent(&players.at(j), countriesInContinent))
                controlContinent = false;
        }
        if (controlContinent)
            score++;
    }
    //3. For each continent, loop through countries and test how many countries this player has
    //4.
    score += playerHand.size();
    return score;
}
// OVERRIDE
int Player::computeScore2(vector<Player *> players, Graph *map)
{
    int score = 0;
    score += getNumOfControlledCountries();
    string continent;
    vector<string> continents;
    //1. Add each continent of player to hashmap
    for (int i = 0; i < countriesOccupied.size(); i++)
    {
        continent = countriesOccupied.at(i).country->getContinent();
        if (std::find(continents.begin(), continents.end(), continent) == continents.end())
        {
            // someName not in name, add it
            continents.push_back(continent);
        }
    }
    //2. For each continent in map, get all countries of continent
    int controlledCountriesInContinent = 0;
    bool controlContinent = true;
    vector<Country> *countriesInContinent;
    for (int i = 0; i < continents.size(); i++)
    {
        countriesInContinent = getCountriesFromContinents(continents.at(i), map);
        controlContinent = true;
        controlledCountriesInContinent = getNumOfCountriesInContinent(this, countriesInContinent);
        for (int j = 0; j < players.size(); j++)
        {
            if (controlledCountriesInContinent < getNumOfCountriesInContinent(players.at(j), countriesInContinent))
                controlContinent = false;
        }
        if (controlContinent)
            score++;
    }
    //3. For each continent, loop through countries and test how many countries this player has
    //4.
    score += playerHand.size();
    return score;
}

bool Player::isControlCountry(Country *country)
{
    int maxControlPoints = 0;
    int controlPoints = 0;
    Player controller;
    for (int i = 0; i < country->playersInCountry.size(); i++)
    {
        controlPoints = country->playersInCountry.at(i).numberArmies + country->playersInCountry.at(i).numOfCities;
        //define what happens if same controlPoints
        if (controlPoints > maxControlPoints)
        {
            maxControlPoints = controlPoints;
            controller = (*country->playersInCountry.at(i).playerOccupying);
        }
    }
    if (controller.getPlayerName() == this->getPlayerName())
        return true;
    return false;
}

void Player::addCountryOccupied(Country *country, int numOfArmies, int numOfCities)
{
    OccupiedCountry newCountryInPlayer = OccupiedCountry();
    newCountryInPlayer.numberArmies = numOfArmies;
    newCountryInPlayer.country = country;
    newCountryInPlayer.numberCities = numOfCities;
    // add it to vector
    countriesOccupied.push_back(newCountryInPlayer);
}

bool Player::ignore()
{
    string yn;
    cout << "Do you want to ignor this action? (y/n): ";
    cin >> yn;
    if (yn == "y")
    {
        cout << "You took the card and ignore this action" << endl;
        string msg = "Player [" + this->getPlayerName() + "] took the card and ignore the action";
        Notify2(msg);
        return true;
    }
    else
    {
        return false;
    }
}

/*
print the information of the player
Name, age, tokens, army color, number of army
*/
void Player::print()
{
    cout << "Player *[" << playerName << "]*, Age: " << playerAge;
    cout << ", owns " << numOfArmies << " \"" << armyColor << "\" armies, ";
    cout << this->getNumOfTokens() << " token(s), " << numOfCities << " cities, ";
    cout << numOfCards << " card(s) " << endl;
}
void Player::printCountries()
{
    cout << this->getPlayerName() << " has ";
    for (int i = 0; i < this->countriesOccupied.size(); ++i)
    {
        if (this->countriesOccupied.at(i).numberArmies > 0)
        {
            cout << this->countriesOccupied.at(i).numberArmies << " army(s) in " << this->countriesOccupied.at(i).country->getName() << "[" << this->countriesOccupied.at(i).country->getContinent() << "] - " << endl;
        }
    }
}
#endif

// STATISTICS
// destroy, move, or place (conquering region)
// use: isControlCountry for move and place army
// if I'm in control before, dont update