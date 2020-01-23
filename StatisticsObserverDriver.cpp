// StatisticObserverDriver.cpp
#include "StatisticsObserver.cpp"
#include <iostream>
#include "MainGameLoopP3.cpp"
#include <vector>

using namespace std;

int main()
{
    // make a map to play the game
    // using MainGameLoop rather than StartGame function selectAndLoadMap()
    MainGameLoopP3 startgame = MainGameLoopP3();
    Graph *graph = startgame.selectAndLoadMap();
    
    cout << endl;

    // Observable objects
    vector<Player *> players;
    players.push_back(new Player("Tino","blue",25,10));
    players.push_back(new Player("Brenden","green",22,10));
    players.push_back(new Player("Tahar","red",22,10));
    players.push_back(new Player("Jinchen","purple",21,10));

    // set strategy for each player, armies, and cities
    players.at(0)->setStrategy(0);
    players.at(1)->setStrategy(0);
    players.at(2)->setStrategy(0);
    players.at(3)->setStrategy(0);

    // Observer object
    StatisticsObserver *view = new StatisticsObserver(); // delete at the end ..
    // attach players to the observer
    view->addObservablePlayer( players.at(0) );
    view->addObservablePlayer( players.at(1) );
    view->addObservablePlayer( players.at(2) );
    view->addObservablePlayer( players.at(3) );
    // attach view to each player
    players.at(0)->Attach(view);
    players.at(1)->Attach(view);
    players.at(2)->Attach(view);
    players.at(3)->Attach(view);

    // populate map
    graph->arr[5].country->addPlayerInCountry( players.at(0),20,20);
    graph->arr[6].country->addPlayerInCountry( players.at(0),20,20);
    graph->arr[6].country->addPlayerInCountry( players.at(1),20,20);
    graph->arr[4].country->addPlayerInCountry( players.at(1),20,20);
    // populate map
    players.at(0)->addCountryOccupied(graph->arr[5].country,20,20);
    players.at(0)->addCountryOccupied(graph->arr[6].country,20,20);
    players.at(1)->addCountryOccupied(graph->arr[6].country,20,20);
    players.at(1)->addCountryOccupied(graph->arr[4].country,20,20);
    
    // countries from Continent 1
    vector<Country> *countries = getCountriesFromContinents("C1",graph);
    for(int i = 0; i < countries->size(); i++)
    {
        cout << countries->at(i).getName();
    }
    cout << endl;

    // then make each player do actions that would NOTIFY() AND UPDATE()
    // TINO
    players.at(0)->buildCity(graph);
    // BRENDEN
    players.at(1)->destroyArmy(graph, players);
    // BRENDEN
    players.at(1)->placeNewArmies(graph);
    // TINO
    players.at(0)->moveArmies(graph, false);
    players.at(0)->moveArmies(graph, false);
    players.at(0)->moveArmies(graph, false);


    // Cards
    Deck *deck = new Deck();
    deck->draw();
    deck->draw();
    deck->draw();
    deck->draw();
    deck->draw();
    deck->draw();

    // just give all 4 players the same cards (from the first 6 drawn cards) 
    for (int i = 0 ; i < players.size() ; i++)
    {
        players.at(i)->playerHand.push_back( deck->cardSpace.at(0) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(1) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(2) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(3) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(4) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(5) );
        players.at(i)->playerHand.push_back( deck->cardSpace.at(0) ); // repeat, to give enough
    }

    // with 4 players, when they all have 8 cards, game is over ...
    players.at(0)->chooseExchange_withPlayers(deck, players);
    players.at(1)->chooseExchange_withPlayers(deck, players);
    players.at(2)->chooseExchange_withPlayers(deck, players);
    players.at(3)->chooseExchange_withPlayers(deck, players);
    // game should end since all 4 players have 8 cards (with an update...)

    // compute scores ...
    cout << "SCORES: " << endl; 
    for (int i = 0; i < players.size(); i++)
    {
        cout << "SCORE of: " << players.at(i)->getPlayerName() << " -> " << players.at(i)->computeScore2(players,graph) << endl;
    }
    

    // END
    return 0;
}