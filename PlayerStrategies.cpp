// BiddingRoom.h file
#ifndef PLAYERSTRATEGIES_CPP
#define PLAYERSTRATEGIES_CPP

#include <string>
#include "PlayerStrategies.h"
#include "CardsFactory.cpp"
#include "Country.cpp"

using namespace std;

PlayerStrategy::PlayerStrategy(Player *playerP) : player(playerP)
{
}

PlayerStrategy::PlayerStrategy()
{
}

CompPlayer::CompPlayer(Player *playerP) : PlayerStrategy(playerP)
{
}

CompPlayer::CompPlayer() : PlayerStrategy()
{
}

InteractivePlayer::InteractivePlayer(Player *playerP) : PlayerStrategy(playerP)
{
}

InteractivePlayer::InteractivePlayer() : PlayerStrategy()
{
}

GreedyPlayer::GreedyPlayer(Player *playerP) : CompPlayer(playerP)
{
}

GreedyPlayer::GreedyPlayer() : CompPlayer()
{
}

ModeratePlayer::ModeratePlayer(Player *playerP) : CompPlayer(playerP)
{
}

ModeratePlayer::ModeratePlayer() : CompPlayer()
{
}

int GreedyPlayer::getBuildCityOrDestroyCard(Deck *deck)
{
    Card *card;
    for (int cardIndex = 0; cardIndex < deck->cardSpace.size(); cardIndex++)
    {
        card = deck->cardSpace.at(cardIndex);
        if (card->getAction().find(preferredAction1) != std::string::npos || card->getAction().find(preferredAction2) != std::string::npos)
        {
            return cardIndex;
        }
    }
    return rand() % deck->cardSpace.size();
}

string InteractivePlayer::chooseExchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    cardChoice--;
    string actions = deck->exchange_new(cardChoice, *player);
    //deck->draw();
    return actions;
}
// needed to overload
string InteractivePlayer::chooseExchange(Deck *deck, vector<Player *> players)
{
    // 2 players - 13 cards (ENDS)
    // 3 players - 10 cards (ENDS)
    // 4 players - 8 cards (ENDS)
    // 5 players - 7 cards (ENDS)
    // Check number of players, and check if all players have the maximum number of cards (at same time)
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    string action = deck->exchange_new(cardChoice, *player);
    //deck->draw();

    // after drawing card
    if (players.size() == 2) // (2-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 13)
            {
                countFinished++;
            }
        }
        if (countFinished == 2) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 3) // (3-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 10)
            {
                countFinished++;
            }
        }
        if (countFinished == 3) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 4) // (4-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 8)
            {
                countFinished++;
            }
        }
        if (countFinished == 4) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 5) // (5-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 7)
            {
                countFinished++;
            }
        }
        if (countFinished == 5) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    return action;
}

vector<string> InteractivePlayer::chooseExchange2(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    cardChoice--;
    vector<string> actions = deck->exchange_new2(cardChoice, *player);
    //deck->draw();

    return actions;
}

Card *InteractivePlayer::exchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    cardChoice--;
    Card *card = deck->exchange(cardChoice, *player);
    //deck->draw();

    return card;
}

void InteractivePlayer::placeNewArmies(Graph *graph)
{
    // Observer: who is controlling country before placing army?
    // If a new player controls a country, Update()

    //check if the player has available army
    if (player->getNumOfArmies() >= 14)
    {
        cout << "Sorry, you have no availabe army to place" << endl;
        return;
    }
    else
    {
        player->setNumOfArmies(player->getNumOfCities() + 1);
    }

    // 2 options
    bool flagForWhile = false;
    do
    {
        int option;
        cout << "Choose an option to place an army (1 or 2): " << endl;
        cout << "1: Place an army in a Country where you have cities " << endl;
        cout << "2: Place army on starting region " << endl;
        cin >> option;

        // 1: Place an army in a Country where you have cities
        if (option == 1)
        {
            // country index
            int index;
            bool flag = false;
            if (player->countriesOccupied.size() > 0) // If player has countries occupied (regions)
            {
                cout << "Here are the countries where you have a city " << endl;
                for (int i = 0; i < player->countriesOccupied.size(); i++)
                {
                    if (player->countriesOccupied.at(i).numberCities > 0) // must at least have 1 city
                    {
                        flag = true;
                        flagForWhile = true;
                        cout << "Country index: " << (i + 1) << endl;
                        cout << "Country name: " << player->countriesOccupied.at(i).country->getName() << endl;
                        cout << "You have " << player->countriesOccupied.at(i).numberCities << " city(s) in this region" << endl;
                    }
                }
                //if no city, continue
                if (flag == false)
                {
                    cout << "Sorry, u dont have a city in any coutry" << endl;
                    continue;
                }
                cout << "Please input a Country-ID where you have a city" << endl;
                cin >> index;
                index--;
                // countriesOccupied.at(index) is the country with built city(s), where the player wants to add army
                // 1) find the country object in the graph, update its vector 'playersInCountry'
                // 2) then update vector of player 'countriesOccupied'
                for (int i = 0; i < graph->V; i++)
                {
                    if (player->countriesOccupied.at(index).country->getName() == graph->arr[i].country->getName()) // found the country in Map
                    {
                        // Observer (before adding army to country)
                        bool playerControlsAlready = false;
                        if (player->isControlCountry(graph->arr[i].country) == true)
                        {
                            // player already controls country: No Update()
                            playerControlsAlready = true;
                        }

                        // modify Player vector
                        player->countriesOccupied.at(index).numberArmies++; // Add 1 army
                        cout << "Adding 1 army to Player's object countriesOccupied ..." << endl;

                        // modify Country vector (country located in graph)
                        // find (this) player and update it
                        for (int k = 0; k < graph->arr[i].country->playersInCountry.size(); k++)
                        {
                            if (player->getPlayerName() == graph->arr[i].country->playersInCountry.at(k).playerOccupying->getPlayerName())
                            {
                                graph->arr[i].country->playersInCountry.at(k).numberArmies++; // Add 1 army
                                cout << "Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;
                            }
                        }

                        // Observer (after occupying country)
                        // If a new player controls a country, Update()
                        if (playerControlsAlready == false) // means 'this player' could be controling the country now
                        {
                            if (player->isControlCountry(graph->arr[i].country) == true)
                            {
                                // means player didn't control before, but now he controls the country: Update() Observer
                                string msg = "Update: After placing new army, " + player->getPlayerName() + " is controling region";
                                player->Notify(msg);
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "Player not occupying any country (no cities or armies)" << endl;
            }
        }

        // 2: Place army on Starting Region
        // starting region ==> graph.arr[ ZERO ].country  (i.e. first country in Map)
        if (option == 2)
        {
            flagForWhile = true;
            bool alreadyInRegion = false;
            // if player is already in the starting region, place army
            for (int i = 0; i < player->countriesOccupied.size(); i++)
            {
                // starting region name: graph.arr[0].country->getName()
                if (player->countriesOccupied.at(i).country->getName() == graph->arr[0].country->getName())
                {
                    // Observer (before adding army to 'starting region' that we already occupy)
                    bool playerControlsAlready = false;
                    if (player->isControlCountry(graph->arr[0].country) == true)
                    {
                        // player already controls 'starting region': No Update()
                        playerControlsAlready = true;
                    }

                    // means we are already in the region
                    alreadyInRegion = true;
                    cout << "Player is already occupying the starting region ..." << endl;

                    // add army to the starting region, that we already occupy
                    // update player's vector
                    player->countriesOccupied.at(i).numberArmies++; // Add 1 army
                    cout << "Adding 1 army to Player's object countriesOccupied ..." << endl;

                    // update country's vector
                    // find (this) player and update it
                    for (int k = 0; k < graph->arr[i].country->playersInCountry.size(); k++)
                    {
                        if (player->getPlayerName() == graph->arr[i].country->playersInCountry.at(k).playerOccupying->getPlayerName())
                        {
                            graph->arr[i].country->playersInCountry.at(k).numberArmies++; // Add 1 army
                            cout << "Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;
                        }
                    }

                    // Observer (after adding army to  starting region, that we already occupied)
                    // If a new player controls a country, Update()
                    if (playerControlsAlready == false) // means 'this player' could be controling the country now
                    {
                        if (player->isControlCountry(graph->arr[0].country) == true)
                        {
                            // means player didn't control before, but now he controls the country: Update() Observer
                            string msg = "Update: After placing new army, " + player->getPlayerName() + " is controling region";
                            player->Notify(msg);
                        }
                    }
                }
            }

            // if player is not in that region yet, place him there and place 1 army
            if (alreadyInRegion == false)
            {
                // Observer (before adding army to 'starting region' that we already occupy)
                bool playerControlsAlready = false;
                if (player->isControlCountry(graph->arr[0].country) == true)
                {
                    // player already controls 'starting region': No Update()
                    playerControlsAlready = true;
                }

                // occupy region and add 1 army
                player->addCountryOccupied(graph->arr[0].country, 1, 0);
                cout << "Occupying country, and Adding 1 army to Player's object countriesOccupied ..." << endl;

                graph->arr[0].country->addPlayerInCountry(player, 1, 0);
                cout << "Occupating country,and Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;

                // Observer (after adding army to  starting region, that we already occupied)
                // If a new player controls a country, Update()
                if (playerControlsAlready == false) // means 'this player' could be controling the country now
                {
                    if (player->isControlCountry(graph->arr[0].country) == true)
                    {
                        // means player didn't control before, but now he controls the country: Update() Observer
                        string msg = "Update: After placing new army, " + player->getPlayerName() + " is controling region";
                        player->Notify(msg);
                    }
                }
            }
        }
    } while (!flagForWhile);
}

void InteractivePlayer::moveArmies(Graph *map, bool byWater)
{
    // Observer: who is controlling country before placing army?
    // If a new player controls a country, Update()

    cout << "Here are the country that you have at least one army:" << endl;
    //traverse the player's vector
    for (int i = 0; i < player->countriesOccupied.size(); ++i)
    {
        if (player->countriesOccupied.at(i).numberArmies > 0)
        {
            cout << (i + 1) << "." << player->countriesOccupied.at(i).country->getName();
            cout << ", armies: " << player->countriesOccupied.at(i).numberArmies << endl;
        }
    }
    cout << endl;
    //prompt the player enters the country id which they want to move an army out
    int id;
    if (player->countriesOccupied.size() != 0)
    {
        cout << "Please selet one country which you want to move an army out: ";
        cin >> id;
        string cName = player->countriesOccupied.at(id - 1).country->getName();
        cout << "The country you chose: " << cName << endl;
        //display the adjacent countries
        cout << "Here are the countries you can move to: " << endl;
        vector<Country> *aCountries = getAdjacencyCountries(cName, map, byWater);
        if (aCountries->size() > 0)
        {
            for (int i = 0; i < aCountries->size(); ++i)
            {
                cout << (i + 1) << ". " << aCountries->at(i).getName() << "[" << aCountries->at(i).getContinent() << "]" << endl;
            }
            int moveID;
            //prompt the player enters the moveID
            cout << "Please input the Country ID which you want to move in: ";
            cin >> moveID;
            //get the destination country's name
            string des = aCountries->at(moveID - 1).getName();
            cout << "You will move one army from [" << cName << "] to [" << des << "]" << endl;
            //update the player's vector
            //find the departure country in the vector
            //if the numA is 0, we should delete the objects from both two vectors
            bool noArmyAndCity = false;
            for (int i = 0; i < player->countriesOccupied.size(); ++i)
            {
                if (player->countriesOccupied.at(i).country->getName() == cName)
                {
                    int numA = --player->countriesOccupied.at(i).numberArmies;
                    int numCity = player->countriesOccupied.at(i).numberCities;
                    noArmyAndCity = (numA == 0) && (numCity == 0);
                    //if the player has no army and city
                    if (noArmyAndCity)
                    {
                        player->countriesOccupied.erase(player->countriesOccupied.begin() + i);
                    }
                    break;
                }
            }
            //find the player in country's vecotor
            //traverse the map to find the country
            for (int i = 0; i < map->V; ++i)
            {
                if (map->arr[i].country->getName() == cName)
                {
                    //find the player
                    for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
                    {
                        if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == player->getPlayerName())
                        {
                            //updata the vector
                            map->arr[i].country->playersInCountry.at(j).numberArmies--;

                            //if the player has no army and city in this country, delete it from the vector
                            if (noArmyAndCity)
                            {
                                map->arr[i].country->playersInCountry.erase(map->arr[i].country->playersInCountry.begin() + j);
                            }
                            break;
                        }
                    }
                    break;
                }
            }

            //update the destination country to player
            bool isNewCountry = true;
            for (int i = 0; i < player->countriesOccupied.size(); ++i)
            {
                if (player->countriesOccupied.at(i).country->getName() == des)
                {
                    player->countriesOccupied.at(i).numberArmies++;
                    isNewCountry = false;
                }
            }

            //traverse the map to find the destination country
            for (int i = 0; i < map->V; ++i)
            {
                if (map->arr[i].country->getName() == des)
                {
                    // Observer (before moving army to new region 'destination')
                    bool playerControlsAlready = false;
                    if (player->isControlCountry(map->arr[i].country) == true)
                    {
                        // player already controls country: No Update()
                        playerControlsAlready = true;
                    }

                    //traverse the vector to find the player
                    for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
                    {
                        if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == player->getPlayerName())
                        {
                            //update the vector in country
                            map->arr[i].country->playersInCountry.at(j).numberArmies++;

                            // Observer: after moving armies, the player could now be controlling that country
                            if (playerControlsAlready == false) // means 'this player' could be controling the country now
                            {
                                if (player->isControlCountry(map->arr[i].country) == true)
                                {
                                    // means player didn't control before, but now he controls the country: Update() Observer
                                    string msg = "Update: After moving army, " + player->getPlayerName() + " is controling region";
                                    player->Notify(msg);
                                }
                            }

                            break;
                        }
                    }
                    break;
                }
            }
            //if the country occupied is new, then we should create new country and player
            //objects and add them into two vectors repectively
            if (isNewCountry)
            {
                //find the country object
                for (int i = 0; i < map->V; ++i)
                {
                    if (map->arr[i].country->getName() == des)
                    {
                        // Observer (before moving army to new region 'destination')
                        bool playerControlsAlready = false;
                        if (player->isControlCountry(map->arr[i].country) == true)
                        {
                            // player already controls country: No Update()
                            playerControlsAlready = true;
                        }

                        //add to the player
                        player->addCountryOccupied(map->arr[i].country, 1, 0);
                        //add to the country
                        map->arr[i].country->addPlayerInCountry(player, 1, 0);

                        // Observer: after moving armies, the player could now be controlling that country
                        if (playerControlsAlready == false) // means 'this player' could be controling the country now
                        {
                            if (player->isControlCountry(map->arr[i].country) == true)
                            {
                                // means player didn't control before, but now he controls the country: Update() Observer
                                string msg = "Update: After moving army, " + player->getPlayerName() + " is controling region";
                                player->Notify(msg);
                            }
                        }

                        break;
                    }
                }
            }

            cout << "Successfully moved an army from [" << cName << "] to [" << des << "]" << endl;
        }
        else
        {
            cout << "Could not move army because the country you chose does not have adjacent countries" << endl;
        }
    }
    else
    {
        cout << "Could not move Army because you have no controlled countries" << endl;
    }
}

void InteractivePlayer::play(Card * card, Graph * graph, vector<Player*> players, Player * player){
    card->takeActions(player,graph,players);
}
void CompPlayer::play(Card * card, Graph * graph, vector<Player*> players, Player * player){
    card->takeActionsComputer(player,graph,players);
}
void InteractivePlayer::moveOverLand(Graph *map)
{
    moveArmies(map, false);
}
void InteractivePlayer::moveOverLandAndWater(Graph *map)
{
    moveArmies(map, true);
}

void InteractivePlayer::buildCity(Graph *map)
{
    /*
    if(numOfCities >3){
        cout << "You cannot build city any more"<<endl;
    }else{
        cout << "You can build a city in these countries: " << endl;
        cout << "Please select one country where you wanna build a city"<<endl;
        numOfCities += 1;
    }
    */

    if (player->getNumOfCities() >= 3)
    {
        cout << "Sorry, you cannot build a city any more" << endl;
        return;
    }
    player->setNumOfCities(player->getNumOfCities() + 1);
    //display the countries where the player can build a city
    cout << "here are the countries where you can build a city: " << endl;
    for (int i = 0; i < player->countriesOccupied.size(); i++)
    {
        if (player->countriesOccupied.at(i).numberArmies > 0)
        {
            cout << (i + 1) << ". " << player->countriesOccupied.at(i).country->getName() << endl;
        }
    }

    //prompt the player enters the country ID which he/she wants to build a city
    int num;
    cout << "please input Country ID which you want to build a city: ";
    cin >> num;
    //update the country's vector
    player->countriesOccupied.at(num - 1).numberCities++;
    //get the country name from the id
    string city = player->countriesOccupied.at(num - 1).country->getName();
    cout << "The city will be built in " << city << endl;
    //traverse the map
    for (int i; i < map->V; i++)
    {
        //find the country in the map
        if (map->arr[i].country->getName() == city)
        {
            //cross through the country's vector
            for (int j = 0; j < map->arr[i].country->playersInCountry.size(); j++)
            {
                //find the player in the country's vector
                if (player->getPlayerName() == map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName())
                {
                    map->arr[i].country->playersInCountry.at(j).numOfCities++;
                    break;
                }
            }
            break;
        }
    }
    //update the player's vector
    //traverse the vector to find the country
    for (int i; i < player->countriesOccupied.size(); ++i)
    {
        if (player->countriesOccupied.at(i).country->getName() == city)
        {
            player->countriesOccupied.at(i).numberCities++;
            break;
        }
    }
    cout << "Congratualation! The city has been built successfully" << endl;
}

void InteractivePlayer::destroyArmy(Graph *map, vector<Player *> players)
{
    //prompt the player selects an enemy
    cout << "Here are the list of enemies: " << endl;
    //traverse the vector to print the names of enemies
    for (int i = 0; i < players.size(); ++i)
    {
        if (players.at(i)->getPlayerName() != player->getPlayerName())
        {
            cout << (i + 1) << ". " << players.at(i)->getPlayerName() << endl;
        }
    }
    int enemyID;
    cout << "Input an Enemy ID: ";
    cin >> enemyID;
    //get the enemy name;
    string enemy = players.at(enemyID - 1)->getPlayerName();
    cout << "One of " << enemy << "\'s army will be destroyed" << endl;
    //displayer the enemy's occupying countries and number of armies
    cout << "Here are the countries where you can destroy " << enemy << "\'s army" << endl;
    for (int i = 0; i < players.at(enemyID - 1)->countriesOccupied.size(); ++i)
    {
        int numA = players.at(enemyID - 1)->countriesOccupied.at(i).numberArmies;
        if (numA > 0)
        {
            string enemyCountry = players.at(enemyID - 1)->countriesOccupied.at(i).country->getName();
            cout << (i + 1) << ". [" << enemyCountry << "] with " << numA << "army(s)" << endl;
        }
    }

    //prompt the player chooses a Country to destory an army
    int enemyCountryID;
    cout << "Input a Country ID: ";
    cin >> enemyCountryID;
    //if the enemy has no army and city after destoying an army, delete it from two vectors
    bool noArmyandCity = false;
    //get the country name
    Player *p1 = players.at(enemyID - 1);
    vector<Player::OccupiedCountry> countriesOpd = players.at(enemyID - 1)->countriesOccupied;
    Country *c1 = players.at(enemyID - 1)->countriesOccupied.at(enemyCountryID - 1).country;

    string enemyCountry = players.at(enemyID - 1)->countriesOccupied.at(enemyCountryID - 1).country->getName();

    cout << "One of " << enemy << "\'s army in " << enemyCountry << " will be destroyed" << endl;
    //update the enemy's vector
    for (int i = 0; i < players.at(enemyID - 1)->countriesOccupied.size(); ++i)
    {
        if (players.at(enemyID - 1)->countriesOccupied.at(i).country->getName() == enemyCountry)
        {
            int n = --players.at(enemyID - 1)->countriesOccupied.at(i).numberArmies;
            int nc = players.at(enemyID - 1)->countriesOccupied.at(i).numberCities;
            noArmyandCity = (n == 0) && (nc == 0);
            if (noArmyandCity)
            {
                //if has no army and city, delete the coutry object from the enemy
                players.at(enemyID - 1)->countriesOccupied.erase(players.at(enemyID - 1)->countriesOccupied.begin() + i);
            }
            break;
        }
    }
    //update the country's vector
    //traverse the map to find the country
    for (int i = 0; map->V; ++i)
    {
        if (enemyCountry == map->arr[i].country->getName())
        {
            //traverse the country's vector
            for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
            {
                if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == enemy)
                {
                    map->arr[i].country->playersInCountry.at(j).numberArmies--;
                    if (noArmyandCity)
                    {
                        //delete the player object if has no army and city
                        map->arr[i].country->playersInCountry.erase(map->arr[i].country->playersInCountry.begin() + j);
                    }
                    break;
                }
            }
            break;
        }
    }
    cout << "One of " << enemy << "\'s army in " << enemyCountry << " has been destroyed successfully" << endl;
}
Card *GreedyPlayer::exchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space and DESTROY YOUR ENEMY (GREEDY):" << endl;
    deck->printCardSpace();
    cardChoice = getBuildCityOrDestroyCard(deck);
    //string action = deck->exchange_new(cardChoice, *player);
    //cardChoice--;
    Card *card = deck->exchange(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << " -- ACTION TO PERFORM (GREED): " << card->getAction() << endl;

    return card;
}
Card *ModeratePlayer::exchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space and DESTROY YOUR ENEMY (GREEDY):" << endl;
    deck->printCardSpace();
    cardChoice = getPlaceNewArmiesCard(deck);
    //string action = deck->exchange_new(cardChoice, *player);
    //cardChoice--;
    Card *card = deck->exchange(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << " -- ACTION TO PERFORM (MODERATE): " << card->getAction() << endl;

    return card;
}
string GreedyPlayer::chooseExchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space and DESTROY YOUR ENEMY (GREEDY):" << endl;
    deck->printCardSpace();
    cardChoice = getBuildCityOrDestroyCard(deck);
    string action = deck->exchange_new(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << "ACTION TO PERFORM (GREED): " << action.at(0) << endl;
    deck->draw();

    return action;
}
// needed to overload this method
string GreedyPlayer::chooseExchange(Deck *deck, vector<Player *> players)
{
    // 2 players - 13 cards (ENDS)
    // 3 players - 10 cards (ENDS)
    // 4 players - 8 cards (ENDS)
    // 5 players - 7 cards (ENDS)
    // Check number of players, and check if all players have the maximum number of cards (at same time)
    int cardChoice = 0;
    cout << "Choose card from card space and DESTROY YOUR ENEMY (GREEDY):" << endl;
    deck->printCardSpace();
    cardChoice = getBuildCityOrDestroyCard(deck);
    string action = deck->exchange_new(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << "ACTION TO PERFORM (GREED): " << action << endl;
    deck->draw();

    // after drawing card
    if (players.size() == 2) // (2-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 13)
            {
                countFinished++;
            }
        }
        if (countFinished == 2) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 3) // (3-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 10)
            {
                countFinished++;
            }
        }
        if (countFinished == 3) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 4) // (4-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 8)
            {
                countFinished++;
            }
        }
        if (countFinished == 4) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 5) // (5-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 7)
            {
                countFinished++;
            }
        }
        if (countFinished == 5) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    return action;
}

vector<string> GreedyPlayer::chooseExchange2(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    cardChoice--;
    vector<string> actions = deck->exchange_new2(cardChoice, *player);
    deck->draw();

    return actions;
}

// Card* GreedyPlayer::exchange(Deck *deck)
// {
//     int cardChoice = 0;
//     cout << "Choose card from card space:" << endl;
//     deck->printCardSpace();
//     cin >> cardChoice;
//     cardChoice--;
//     Card *card = deck->exchange(cardChoice, *player);
//     //deck->draw();

//     return card;
// }

int ModeratePlayer::getPlaceNewArmiesCard(Deck *deck)
{
    Card *card;
    for (int cardIndex = 0; cardIndex < deck->cardSpace.size(); cardIndex++)
    {
        card = deck->cardSpace.at(cardIndex);
        if (card->getAction().find(preferredAction1) != std::string::npos)
        {
            return cardIndex;
        }
    }
    return rand() % deck->cardSpace.size();
}

string ModeratePlayer::chooseExchange(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space and keep control (MODERATE PLAYER):" << endl;
    deck->printCardSpace();
    cardChoice = getPlaceNewArmiesCard(deck);
    string action = deck->exchange_new(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << "ACTION TO PERFORM (MODERATE): " << action.at(0) << endl;

    deck->draw();

    return action;
}
// needed to overload this method
string ModeratePlayer::chooseExchange(Deck *deck, vector<Player *> players)
{
    // 2 players - 13 cards (ENDS)
    // 3 players - 10 cards (ENDS)
    // 4 players - 8 cards (ENDS)
    // 5 players - 7 cards (ENDS)
    // Check number of players, and check if all players have the maximum number of cards (at same time)
    int cardChoice = 0;
    cout << "Choose card from card space and keep control (MODERATE PLAYER):" << endl;
    deck->printCardSpace();
    cardChoice = getPlaceNewArmiesCard(deck);
    string action = deck->exchange_new(cardChoice, *player);
    cout << "CHOICE : " << cardChoice << "ACTION TO PERFORM (MODERATE): " << action << endl;

    deck->draw();

    // after drawing card
    if (players.size() == 2) // (2-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 13)
            {
                countFinished++;
            }
        }
        if (countFinished == 2) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 3) // (3-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 10)
            {
                countFinished++;
            }
        }
        if (countFinished == 3) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 4) // (4-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 8)
            {
                countFinished++;
            }
        }
        if (countFinished == 4) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    if (players.size() == 5) // (5-players)
    {
        int countFinished = 0;
        for (int i = 0; i < players.size(); i++)
        {
            if (players.at(i)->playerHand.size() == 7)
            {
                countFinished++;
            }
        }
        if (countFinished == 5) // all players have max number of cards
        {
            // game is finished
            string msg = "Update: Congratulations, after " + player->getPlayerName() + " picked a card, the game arrived to the End.";
            player->Notify(msg);
        }
    }

    return action;
}

// Card* ModeratePlayer::exchange(Deck *deck)
// {
//     int cardChoice = 0;
//     cout << "Choose card from card space:" << endl;
//     deck->printCardSpace();
//     cin >> cardChoice;
//     cardChoice--;
//     Card *card = deck->exchange(cardChoice, *player);
//     //deck->draw();

//     return card;
// }
vector<string> ModeratePlayer::chooseExchange2(Deck *deck)
{
    int cardChoice = 0;
    cout << "Choose card from card space:" << endl;
    deck->printCardSpace();
    cin >> cardChoice;
    cardChoice--;
    vector<string> actions = deck->exchange_new2(cardChoice, *player);
    deck->draw();
    return actions;
}

void CompPlayer::buildCity(Graph *map)
{
    if (player->getNumOfCities() >= 3)
    {
        cout << "Sorry, you cannot build a city any more" << endl;
        return;
    }
    player->setNumOfCities(player->getNumOfCities() + 1);
    //display the countries where the player can build a city
    cout << "here are the countries where you can build a city: " << endl;

    for (int i = 0; i < player->countriesOccupied.size(); i++)
    {
        if (player->countriesOccupied.at(i).numberArmies > 0)
        {
            cout << (i + 1) << ". " << player->countriesOccupied.at(i).country->getName() << endl;
        }
    }

    //prompt the player enters the country ID which he/she wants to build a city
    int num;
    cout << "please input Country ID which you want to build a city: ";
    //cin >> num;
    num = (rand() % player->countriesOccupied.size()) + 1;
    //update the country's vector
    player->countriesOccupied.at(num - 1).numberCities++;
    //get the country name from the id
    string city = player->countriesOccupied.at(num - 1).country->getName();
    cout << "The city will be built in " << city << endl;
    //traverse the map
    for (int i; i < map->V; i++)
    {
        //find the country in the map
        if (map->arr[i].country->getName() == city)
        {
            //cross through the country's vector
            for (int i = 0; i < map->arr[i].country->playersInCountry.size(); i++)
            {
                //find the player in the country's vector
                if (player->getPlayerName() == map->arr[i].country->playersInCountry.at(i).playerOccupying->getPlayerName())
                {
                    map->arr[i].country->playersInCountry.at(i).numOfCities++;
                    break;
                }
            }
            break;
        }
    }
    //update the player's vector
    //traverse the vector to find the country
    for (int i; i < player->countriesOccupied.size(); ++i)
    {
        if (player->countriesOccupied.at(i).country->getName() == city)
        {
            player->countriesOccupied.at(i).numberCities++;
            break;
        }
    }
    cout << "Congratualation! The city has been built successfully" << endl;
}

void CompPlayer::destroyArmy(Graph *map, vector<Player *> players)
{
    //prompt the player selects an enemy
    cout << "Here are the list of enemies: " << endl;
    //traverse the vector to print the names of enemies
    for (int i = 0; i < players.size(); ++i)
    {
        if (players.at(i)->getPlayerName() != player->getPlayerName())
        {
            cout << (i + 1) << ". " << players.at(i)->getPlayerName() << endl;
        }
    }
    int enemyID;
    cout << "Input an Enemy ID: ";
    enemyID = (rand() % players.size()) + 1;
    //get the enemy name;
    string enemy = players.at(enemyID - 1)->getPlayerName();
    cout << "One of " << enemy << "\'s army will be destroyed" << endl;
    //displayer the enemy's occupying countries and number of armies
    cout << "Here are the countries where you can destroy " << enemy << "\'s army" << endl;
    for (int i = 0; i < players.at(enemyID - 1)->countriesOccupied.size(); ++i)
    {
        int numA = players.at(enemyID - 1)->countriesOccupied.at(i).numberArmies;
        if (numA > 0)
        {
            string enemyCountry = players.at(enemyID - 1)->countriesOccupied.at(i).country->getName();
            cout << (i + 1) << ". [" << enemyCountry << "] with " << numA << "army(s)" << endl;
        }
    }

    //prompt the player chooses a Country to destory an army
    int enemyCountryID;
    cout << "Input a Country ID: ";
    enemyCountryID = (rand() % players.at(enemyID - 1)->countriesOccupied.size()) + 1;
    //if the enemy has no army and city after destoying an army, delete it from two vectors
    bool noArmyandCity = false;
    //get the country name
    string enemyCountry = players.at(enemyID - 1)->countriesOccupied.at(enemyCountryID - 1).country->getName();
    cout << "One of " << enemy << "\'s army in " << enemyCountry << " will be destroyed" << endl;
    //update the enemy's vector
    for (int i = 0; i < players.at(enemyID - 1)->countriesOccupied.size(); ++i)
    {
        if (players.at(enemyID - 1)->countriesOccupied.at(i).country->getName() == enemyCountry)
        {
            int n = --players.at(enemyID - 1)->countriesOccupied.at(i).numberArmies;
            int nc = players.at(enemyID - 1)->countriesOccupied.at(i).numberCities;
            noArmyandCity = (n == 0) && (nc == 0);
            if (noArmyandCity)
            {
                //if has no army and city, delete the coutry object from the enemy
                players.at(enemyID - 1)->countriesOccupied.erase(players.at(enemyID - 1)->countriesOccupied.begin() + i);
            }
            break;
        }
    }
    //update the country's vector
    //traverse the map to find the country
    for (int i = 0; map->V; ++i)
    {
        if (enemyCountry == map->arr[i].country->getName())
        {
            //traverse the country's vector
            for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
            {
                if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == enemy)
                {
                    map->arr[i].country->playersInCountry.at(j).numberArmies--;
                    if (noArmyandCity)
                    {
                        //delete the player object if has no army and city
                        map->arr[i].country->playersInCountry.erase(map->arr[i].country->playersInCountry.begin() + j);
                    }
                    break;
                }
            }
            break;
        }
    }
    cout << "One of " << enemy << "\'s army in " << enemyCountry << " has been destroyed successfully" << endl;
}

void CompPlayer::moveOverLand(Graph *map)
{
    moveArmies(map, false);
}
void CompPlayer::moveOverLandAndWater(Graph *map)
{
    moveArmies(map, true);
}

vector<Country> *PlayerStrategy::getAdjacencyCountries(string cName, Graph *map, bool byWater)
{
    //create a vector that contains all the adjacenct countries
    vector<Country> *aCountries = new vector<Country>;
    //traverse the map
    for (int i = 0; i < map->V; ++i)
    {
        //find the country
        if (map->arr[i].country->getName() == cName)
        {
            //get the continent of the country
            string continent = map->arr[i].country->getContinent();
            //find the first adjacent country
            AdjListNode *current = map->arr[i].head;
            //loop to find all adjacent country
            while (current != NULL)
            {
                //stores the country objects if they are at
                //same continent with the chosen country
                if (current->data.getContinent() == continent)
                {
                    aCountries->push_back(current->data);
                    //if we need to find the adjacent country which is connected by water
                    //to the chosen country
                }
                else if (byWater)
                {
                    aCountries->push_back(current->data);
                }
                //let current points to next adjacent country
                current = current->next;
            }
            break;
        }
    }
    return aCountries;
}

/*
1. choose one of armies
2. which regions can the army move to
3. move to the destination
    */
void CompPlayer::moveArmies(Graph *map, bool byWater)
{
    /*
    cout << "Countries where you have arimies: " << endl;

    cout << "Please select one country"<<endl;

    cout << "You have X armies in this country" << endl;

    cout << "The army can be moved to ..., please select the destination"<<endl;
    */
    cout << "Here are the country that you have at least one army:" << endl;
    //traverse the player's vector
    for (int i = 0; i < player->countriesOccupied.size(); ++i)
    {
        if (player->countriesOccupied.at(i).numberArmies > 0)
        {
            cout << (i + 1) << "." << player->countriesOccupied.at(i).country->getName();
            cout << ", armies: " << player->countriesOccupied.at(i).numberArmies << endl;
        }
    }
    cout << endl;
    //prompt the player enters the country id which they want to move an army out
    int id;
    //check if possible to move army
    if (player->countriesOccupied.size() != 0)
    {
        cout << "Please selet one country which you want to move an army out: ";
        id = (rand() % player->countriesOccupied.size()) + 1;
        string cName = player->countriesOccupied.at(id - 1).country->getName();
        cout << "The country you chose: " << cName << endl;
        //display the adjacent countries
        cout << "Here are the countries you can move to: " << endl;
        vector<Country> *aCountries = getAdjacencyCountries(cName, map, byWater);
        if (aCountries->size() > 0)
        {
            for (int i = 0; i < aCountries->size(); ++i)
            {
                cout << (i + 1) << ". " << aCountries->at(i).getName() << "[" << aCountries->at(i).getContinent() << "]" << endl;
            }
            int moveID;
            //prompt the player enters the moveID
            cout << "Please input the Country ID which you want to move in: ";
            moveID = ((rand() % aCountries->size()) + 1);
            //get the destination country's name
            string des = aCountries->at(moveID - 1).getName();
            cout << "You will move one army from [" << cName << "] to [" << des << "]" << endl;
            //update the player's vector
            //find the departure country in the vector
            //if the numA is 0, we should delete the objects from both two vectors
            bool noArmyAndCity = false;
            for (int i = 0; i < player->countriesOccupied.size(); ++i)
            {
                if (player->countriesOccupied.at(i).country->getName() == cName)
                {
                    int numA = --player->countriesOccupied.at(i).numberArmies;
                    int numCity = player->countriesOccupied.at(i).numberCities;
                    noArmyAndCity = (numA == 0) && (numCity == 0);
                    //if the player has no army and city
                    if (noArmyAndCity)
                    {
                        player->countriesOccupied.erase(player->countriesOccupied.begin() + i);
                    }
                    break;
                }
            }
            //find the player in country's vecotor
            //traverse the map to find the country
            for (int i = 0; i < map->V; ++i)
            {
                if (map->arr[i].country->getName() == cName)
                {
                    //find the player
                    for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
                    {
                        if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == player->getPlayerName())
                        {
                            //updata the vector
                            map->arr[i].country->playersInCountry.at(j).numberArmies--;
                            //if the player has no army and city in this country, delete it from the vector
                            if (noArmyAndCity)
                            {
                                map->arr[i].country->playersInCountry.erase(map->arr[i].country->playersInCountry.begin() + j);
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            //update the destination country to player
            bool isNewCountry = true;
            for (int i = 0; i < player->countriesOccupied.size(); ++i)
            {
                if (player->countriesOccupied.at(i).country->getName() == des)
                {
                    player->countriesOccupied.at(i).numberArmies++;
                    isNewCountry = false;
                }
            }

            //traverse the map to find the destination country
            for (int i = 0; i < map->V; ++i)
            {
                if (map->arr[i].country->getName() == des)
                {
                    //traverse the vector to find the player
                    for (int j = 0; j < map->arr[i].country->playersInCountry.size(); ++j)
                    {
                        if (map->arr[i].country->playersInCountry.at(j).playerOccupying->getPlayerName() == player->getPlayerName())
                        {
                            //update the vector in country
                            map->arr[i].country->playersInCountry.at(j).numberArmies++;
                            break;
                        }
                    }
                    break;
                }
            }
            //if the country occupied is new, then we should create new country and player
            //objects and add them into two vectors repectively
            if (isNewCountry)
            {
                //find the country object
                for (int i = 0; i < map->V; ++i)
                {
                    if (map->arr[i].country->getName() == des)
                    {
                        //add to the player
                        player->addCountryOccupied(map->arr[i].country, 1, 0);
                        //add to the country
                        map->arr[i].country->addPlayerInCountry(player, 1, 0);
                        break;
                    }
                }
            }

            cout << "Successfully moved an army from [" << cName << "] to [" << des << "]" << endl;
        }
        else
        {
            cout << "Could not move army because the country you chose does not have adjacent countries" << endl;
        }
    }
    else
    {
        cout << "Could not move Army because you have no controlled countries" << endl;
    }
}

void CompPlayer::placeNewArmies(Graph *graph)
{
    //cout << "placeNewArmy() method " << endl;

    //check if the player has available army
    if (player->getNumOfArmies() >= 14)
    {
        cout << "Sorry, you have no availabe army to place" << endl;
        return;
    }
    else
    {
        player->setNumOfArmies(player->getNumOfCities() + 1);
    }

    // 2 options
    bool flagForWhile = false;
    do
    {
        int option;
        cout << "Choose an option to place an army (1 or 2): " << endl;
        cout << "1: Place an army in a Country where you have cities " << endl;
        cout << "2: Place army on starting region " << endl;
        if (player->countriesOccupied.size() < 1)
            option = 2;
        else
            option = (rand() % 2) + 1;

        // 1: Place an army in a Country where you have cities
        if (option == 1)
        {
            // country index
            int index;
            bool flag = false;
            if (player->countriesOccupied.size() > 0) // If player has countries occupied (regions)
            {
                cout << "Here are the countries where you have a city " << endl;
                for (int i = 0; i < player->countriesOccupied.size(); i++)
                {
                    if (player->countriesOccupied.at(i).numberCities > 0) // must at least have 1 city
                    {
                        flag = true;
                        flagForWhile = true;
                        cout << "Country index: " << (i + 1) << endl;
                        cout << "Country name: " << player->countriesOccupied.at(i).country->getName() << endl;
                        cout << "You have " << player->countriesOccupied.at(i).numberCities << " city(s) in this region" << endl;
                    }
                }
                //if no city, continue
                if (flag == false)
                {
                    cout << "Sorry, u dont have a city in any coutry" << endl;
                    option = 2;
                }
                else
                {
                    cout << "Please input a Country-ID where you have a city" << endl;
                    index = (rand() % player->countriesOccupied.size()) + 1;
                    index--;
                    // countriesOccupied.at(index) is the country with built city(s), where the player wants to add army
                    // 1) find the country object in the graph, update its vector 'playersInCountry'
                    // 2) then update vector of player 'countriesOccupied'
                    for (int i = 0; i < graph->V; i++)
                    {
                        if (player->countriesOccupied.at(index).country->getName() == graph->arr[i].country->getName()) // found the country in Map
                        {
                            // modify Player vector
                            player->countriesOccupied.at(index).numberArmies++; // Add 1 army
                            cout << "Adding 1 army to Player's object countriesOccupied ..." << endl;

                            // modify Country vector (country located in graph)
                            // find (this) player and update it
                            for (int k = 0; k < graph->arr[i].country->playersInCountry.size(); k++)
                            {
                                if (player->getPlayerName() == graph->arr[i].country->playersInCountry.at(k).playerOccupying->getPlayerName())
                                {
                                    graph->arr[i].country->playersInCountry.at(k).numberArmies++; // Add 1 army
                                    cout << "Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;
                                }
                            }
                        }
                    }
                }
            }
            else
            {
                cout << "Player not occupying any country (no cities or armies)" << endl;
                option = 2;
            }
        }

        // 2: Place army on Starting Region
        // starting region ==> graph.arr[ ZERO ].country  (i.e. first country in Map)
        if (option == 2)
        {
            flagForWhile = true;
            bool alreadyInRegion = false;
            // if player is already in the starting region, place army
            for (int i = 0; i < player->countriesOccupied.size(); i++)
            {
                // starting region name: graph.arr[0].country->getName()
                if (player->countriesOccupied.at(i).country->getName() == graph->arr[0].country->getName())
                {
                    // means we are already in the region
                    alreadyInRegion = true;
                    cout << "Player is already occupying the starting region ..." << endl;

                    // add army to the starting region, that we already occupy
                    // update player's vector
                    player->countriesOccupied.at(i).numberArmies++; // Add 1 army
                    cout << "Adding 1 army to Player's object countriesOccupied ..." << endl;

                    // update country's vector
                    // find (this) player and update it
                    for (int k = 0; k < graph->arr[i].country->playersInCountry.size(); k++)
                    {
                        if (player->getPlayerName() == graph->arr[i].country->playersInCountry.at(k).playerOccupying->getPlayerName())
                        {
                            graph->arr[i].country->playersInCountry.at(k).numberArmies++; // Add 1 army
                            cout << "Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;
                        }
                    }
                }
            }

            // if player is not in that region yet, place him there and place 1 army
            if (alreadyInRegion == false)
            {
                // occupy region and add 1 army
                player->addCountryOccupied(graph->arr[0].country, 1, 0);
                cout << "Occupying country, and Adding 1 army to Player's object countriesOccupied ..." << endl;

                graph->arr[0].country->addPlayerInCountry(player, 1, 0);
                cout << "Occupating country,and Adding 1 army to Player occupying vector in the graph's Country object ..." << endl;
            }
        }
    } while (!flagForWhile);
    cout << endl;
    cout << endl;
}
#endif