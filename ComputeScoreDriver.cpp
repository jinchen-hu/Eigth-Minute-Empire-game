// This is the BiddingRoomDriver.cpp
#include <iostream>
#include <string>
#include "Player.cpp"
#include "MapLoader.cpp"
#include "Cards.cpp"

using namespace std;

Player* determineWinner(vector<Player> players, Graph * graph){
    int score ;
    Player * winner = &players.at(0);
    for(int i = 0; i < players.size(); i++){
        score = players.at(i).computeScore(players,graph);
        cout << players.at(i).getPlayerName() << ": "<< score <<"\n";
        if((score > winner->computeScore(players,graph)))
            winner = &players.at(i);
        else if(score == winner->computeScore(players,graph)){
            if(players.at(i).getNumOfTokens() == winner->getNumOfTokens()){
                if(players.at(i).getNumOfArmies() == winner->getNumOfArmies()){
                    if(players.at(i).getNumOfControlledCountries() > winner->getNumOfControlledCountries())
                        winner = &players.at(i);
                }
                else if(players.at(i).getNumOfArmies() > winner->getNumOfArmies()){
                    winner = &players.at(i);
                }
            }
            else if(players.at(i).getNumOfTokens() > winner->getNumOfTokens()){
                winner = &players.at(i);
            }
        }
    }
    return winner;
}
int main()
{
    // create 4 Players
    vector<Player> players =  { Player("Tino","blue",25,10),
                                Player("Brenden","green",22,10),
                                Player("Tahar","red",22,10),
                                Player("Jinchen","purple",21,10)};


    Graph *graph = createGraph(7);
    cout<<"-----regular map 1-------" << endl;
    bool valid = readMap(graph,"testmap.map");
    if(valid){
        printGraph(graph);
    }
    else{
        printValidationError();
    }
    players.at(0).playerHand = {Card("TEST","CRYSTAL",1)};
    players.at(2).playerHand = {Card("TEST","CRYSTAL",1),Card("TEST","CRYSTAL",1),Card("TEST","WOOD",1)
    ,Card("TEST","WOOD",1),Card("TEST","METAL",1)};
    graph->arr[5].country->addPlayerInCountry(&players.at(0),20,20);
    graph->arr[6].country->addPlayerInCountry(&players.at(1),20,20);
    graph->arr[4].country->addPlayerInCountry(&players.at(1),20,20);
    players.at(0).addCountryOccupied(graph->arr[5].country,20,20);
    players.at(1).addCountryOccupied(graph->arr[6].country,20,20);
    players.at(1).addCountryOccupied(graph->arr[4].country,20,20);
    
    vector<Country> *countries = getCountriesFromContinents("C1",graph);
    for(int i = 0; i < countries->size(); i++){
        cout << countries->at(i).getName();
    }
    int score = players.at(0).computeScore(players,graph);
    int score1 = players.at(1).computeScore(players,graph);
    int score2 = players.at(2).computeScore(players,graph);

    cout << "Scores\n";
    Player * winner = determineWinner(players,graph);
    cout << winner->getPlayerName();
    // Player * winner = &players.at(0);
    // for(int i = 0; i < players.size(); i++){
    //     score = players.at(i).computeScore(players,graph);
    //     cout << players.at(i).getPlayerName() << ": "<< score <<"\n";
    //     if((score > winner->computeScore(players,graph)))
    //         winner = &players.at(i);
    //     else if(score == winner->computeScore(players,graph)){
    //         if(players.at(i).getNumOfTokens() == winner->getNumOfTokens()){
    //             if(players.at(i).getNumOfArmies() == winner->getNumOfArmies()){
    //                 if(players.at(i).getNumOfControlledCountries > winner->getNumOfControlledCountries())
    //                     winner = &players.at(i);
    //             }
    //             else if(players.at(i).getNumOfArmies() > winner->getNumOfArmies()){
    //                 winner = &players.at(i);
    //             }
    //         }
    //         else if(players.at(i).getNumOfArmies() > winner->getNumOfArmies()){
    //             winner = &players.at(i);
    //         }
    //     }

    // }
    delete graph;
    return 0;
}