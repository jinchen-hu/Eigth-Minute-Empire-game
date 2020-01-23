// BiddingRoom.h file
#ifndef PLAYERSTRATEGIES_H
#define PLAYERSTRATEGIES_H

#include "Player.h"
#include "CardsFactory.h"

#include "Map.h"
using namespace std;

class Card;
class Deck;
class PlayerStrategy
{
protected:
    Player *player;

public:
    PlayerStrategy(Player *player);

    PlayerStrategy();

    virtual void buildCity(Graph *map) = 0;

    virtual void destroyArmy(Graph *map, vector<Player *> players) = 0;

    virtual void moveArmies(Graph *map, bool byWater) = 0;

    virtual void moveOverLand(Graph *map) = 0;

    virtual void moveOverLandAndWater(Graph *map) = 0;

    vector<Country> *getAdjacencyCountries(string cName, Graph *map, bool byWater);

    virtual void placeNewArmies(Graph *graph) = 0;

    virtual Card *exchange(Deck *deck) = 0;
    virtual string chooseExchange(Deck *deck) = 0;

    // added this to be able to look up the players cards and the number of players
    virtual string chooseExchange(Deck *deck, vector<Player *> players) = 0;
    virtual vector<string> chooseExchange2(Deck *deck) = 0;
    virtual void play(Card * card, Graph * graph, vector<Player*> players, Player * player) = 0;
};

class InteractivePlayer : public PlayerStrategy
{
public:
    InteractivePlayer(Player *player);

    InteractivePlayer();

    void buildCity(Graph *map);

    void destroyArmy(Graph *map, vector<Player *> players);

    void moveArmies(Graph *map, bool byWater);

    void moveOverLand(Graph *map);

    void moveOverLandAndWater(Graph *map);

    void placeNewArmies(Graph *graph);

    string chooseExchange(Deck *deck);
    Card *exchange(Deck *deck);
    // added this to be able to look up the players cards and the number of players
    string chooseExchange(Deck *deck, vector<Player *> players);
    vector<string> chooseExchange2(Deck *deck);
    void play(Card * card, Graph * graph, vector<Player*> players, Player * player);
};

class CompPlayer : public PlayerStrategy
{

public:
    CompPlayer(Player *player);

    CompPlayer();

    void buildCity(Graph *map);

    void destroyArmy(Graph *map, vector<Player *> players);

    void moveArmies(Graph *map, bool byWater);

    void moveOverLand(Graph *map);

    void moveOverLandAndWater(Graph *map);

    void placeNewArmies(Graph *graph);
    void play(Card * card, Graph * graph, vector<Player*> players, Player * player);

    
};
class GreedyPlayer : public CompPlayer
{
private:
    string const preferredAction1 = "Build a City";
    string const preferredAction2 = "Destroy an Army";

public:
    GreedyPlayer();

    GreedyPlayer(Player *player);
    Card *exchange(Deck *deck);
    string chooseExchange(Deck *deck);
    vector<string> chooseExchange2(Deck *deck);

    // added this to be able to look up the players cards and the number of players
    string chooseExchange(Deck *deck, vector<Player *> players);

    //This method will get a build city or destroy army card index from the cardspace if available
    //If not available wll return a random index.
    int getBuildCityOrDestroyCard(Deck *deck);
};

class ModeratePlayer : public CompPlayer
{
private:
    string const preferredAction1 = "Place New Army";

public:
    ModeratePlayer(Player *player);

    ModeratePlayer();
    Card *exchange(Deck *deck);
    string chooseExchange(Deck *deck);
    vector<string> chooseExchange2(Deck *deck);

    // added this to be able to look up the players cards and the number of players
    string chooseExchange(Deck *deck, vector<Player *> players);

    int getPlaceNewArmiesCard(Deck *deck);
};

#endif