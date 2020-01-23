#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "CardsFactory.h"
#include <vector>
class GameStrategy
{
public:
    virtual void gameStart(vector<Player *> *players, Graph *graph, Deck *deck);
    virtual Graph * chooseMap(Graph *graph) = 0;
    virtual vector<Player *> setUpPlayers() = 0;
};

class TournamentGame : public GameStrategy
{
public:
    //void gameStart(vector<Player *> players, Graph *graph, Deck *deck);
    Graph * chooseMap(Graph *graph);
    vector<Player *> setUpPlayers();
    //void gameStart(vector<Player *> *players, Graph *graph, Deck *deck);
};
class SingleGame : public GameStrategy
{
public:
    //void gameStart(vector<Player *> players, Graph *graph, Deck *deck);
    Graph * chooseMap(Graph *graph);
    vector<Player *> setUpPlayers();
    //void gameStart(vector<Player *> *players, Graph *graph, Deck *deck);
};
class GameEngine
{
protected:
    GameStrategy *_strategy;
    Graph *graph;
    vector<Player *> players;
    Deck *deck;

public:
    void chooseGameType();
    void chooseMap();
    void setUpPlayers();
    void playGame();
    void setStrategy(GameStrategy *);
    void displayScore();
};
#endif