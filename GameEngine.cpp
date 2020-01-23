#ifndef GAMEENGINE_CPP
#define GAMEENGINE_CPP
#include "GameEngine.h"
#include "Helper.cpp"
#include "CardsFactory.cpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

void GameEngine::chooseGameType()
{
    cout << "What type of game do you want to play" << endl;
    cout << "1. Single game" << endl;
    cout << "2. Tournament" << endl;
    int gameType = 1;
    cin >> gameType;
    GameStrategy *_strat;
    if (gameType == 1)
    {
        _strat = new SingleGame();
    }
    else
    {
        _strat = new TournamentGame();
    }
    setStrategy(_strat);
}

void GameEngine::playGame()
{
    deck = createDeck();
    cout << "Each player palces 3 armies at the begining of the game" << endl;
    for (int i = 0; i < players.size(); i++)
    {
        //at the beginning, each player places 3 armies in the starting region
        for (int j = 0; j < 3; j++)
        {
            players.at(i)->placeNewArmies(graph);
        }
        players.at(i)->printCountries();
    }
    _strategy->gameStart(&players, graph, deck);
}

void GameEngine::setStrategy(GameStrategy *strat)
{
    _strategy = strat;
}

void GameStrategy::gameStart(vector<Player *> *players, Graph *graph, Deck *deck)
{
    int turn = 0;
    bool overFlag = false;
    int num = players->size();
    bool *states = new bool[num];
    int maxCards;
    if (num == 2)
    {
        maxCards = 13;
    }
    if (num == 3)
    {
        maxCards = 10;
    }
    if (num == 4)
    {
        maxCards = 8;
    }
    if (num == 5)
    {
        maxCards = 7;
    }
    Card *drawnCard;
    int playersSkipped = 0;
    //Main game loop
    do
    {
        for (int i = 0; i < num; ++i)
        {
            if (players->at(i)->getNumOfTokens() > 0)
            {
                /*
                //check the player state before take actions
                //if the state is true, break the for loop
                if(states[i] == true){
                    break;
                }
                */

                cout << players->at(i)->getPlayerName() << ", please drive a card." << endl;
                //Have the player pick a card from the card space on the board
                drawnCard = players->at(i)->chooseExchange(deck);
                cout << "Action: " << drawnCard->getAction() << endl;
                players->at(i)->print();
                //play the card's action
                players->at(i)->play(drawnCard, graph, *players);
                cout << endl;
                cout << endl;
                //check the player state
                if (players->at(i)->getNumOfCards() == maxCards)
                {
                    overFlag = true;
                }
            }
            else
            {
                cout << players->at(i)->getPlayerName() << ", you cannot continue the game since you do not have coins" << endl;
                //keep track of skipped players
                playersSkipped++;
            }
            //Check if all players have been skipped for lack of coins. If so, the game is over
            if (playersSkipped >= players->size())
            {
                overFlag = true;
            }
        }

        turn++;
    } while (!overFlag && turn <= 30); // the condition should be !overFlag
}

void GameEngine::chooseMap()
{
    graph = _strategy->chooseMap(graph);
}

void GameEngine::setUpPlayers()
{
    players = _strategy->setUpPlayers();
    //players = determineOrder();
}

vector<Player *> SingleGame::setUpPlayers()
{
    //This function is in Helper.cpp
    return determineOrder();
}

vector<Player *> TournamentGame::setUpPlayers()
{
    //This function is in Helper.cpp
    return determineOrderComputer();
}

Graph *SingleGame::chooseMap(Graph *graph)
{
    //This function is in Helper.cpp
    return generateMap();
}

Graph *TournamentGame::chooseMap(Graph *graph)
{
    //This function is in Helper.cpp
    return generateMapComputer();
}

void GameEngine::displayScore()
{
    const char separator = '|';
    const int nameWidth = 6;
    const int numWidth = 8;
    std::cout << std::left;

    std::cout << setw(20) << "[Name]" << setw(30) << "[NUMBER OF CARDS]" << setw(30) << "[NUMBER OF TOKENS]" << setw(9) << "[SCORE]" << '\n';
    for (int i = 0; i < players.size(); i++)
    {

        cout << setw(20) << players.at(i)->getPlayerName() << setw(30)
             << players.at(i)->getNumOfCards() << setw(30) << players.at(i)->getNumOfTokens() << setw(9)
             << players.at(i)->computeScore2(players, graph) << '\n';

        cout << endl;
    }
    Player *winner = determineWinner(players, graph);

    cout << "------------------WINNER!!------------------------------" << endl;
    cout << winner->getPlayerName() << "!";
}

int main()
{
    cout << "WELCOME TO EIGHT MINUTE EMPIRE GAME" << endl;
    GameEngine game;
    game.chooseGameType();
    game.chooseMap();
    game.setUpPlayers();
    game.playGame();
    game.displayScore();
    int i;
    cin >> i;
    return 0;
}
#endif