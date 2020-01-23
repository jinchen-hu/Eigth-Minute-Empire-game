
#include <iostream>
#include <string>

#include "GameStart.cpp"
#include "Player.h"

using namespace std;

int main()
{

    GameStart startgame = GameStart();
    //map
    Graph map = startgame.selectAndLoadMap();
    //players
    vector<Player> players = startgame.createPlayers();
    
    
    // modify both vectors to test:
    // First player has 2 armies and 2 cities in country1
    players.at(0).addCountryOccupied(map.arr[0].country, 2, 2);
    // country is occupied by player1 with 2 armies and 2 cities
    map.arr[0].country->addPlayerInCountry(&players.at(0), 2, 2);
    
    //test function
    players.at(0).placeNewArmies(map);



    /*
    // print Player vector 'countriesOccupied'
    for (int i = 0; i < ply1.countriesOccupied.size(); i++)
    {
        cout << "Countries occupied by ply1: "<< ply1.countriesOccupied.at(i).country.getName();
        cout << " and armies: " << ply1.countriesOccupied.at(i).numberArmies << endl;
    }

    // print Country vector 'playersInCountry'
    for (size_t i = 0; i < country1.playersInCountry.size(); i++)
    {
        cout << "Players in the country1: " << country1.playersInCountry.at(i).playerOccupying->getPlayerName(); 
        cout << " and armies: " << country1.playersInCountry.at(i).numberArmies << endl;
    }
    */
    
    return 0;
}