// StatisticObserverDriver.cpp
#include "StatisticsObserver.cpp"
#include <iostream>
#include "MainGameLoopP3.cpp"
#include <vector>

using namespace std;

int main()
{   
    //load map
    MainGameLoopP3 mainLoop = MainGameLoopP3();
    Graph *map = mainLoop.selectAndLoadMap();
    //create a vector storing players 
    vector<Player*> players;
    //declare the observer
    StatisticsObserver *obs = new StatisticsObserver();
    
    //set each player's information
    int num;
    do{
        cout << "Please set the number of players: ";
        cin >> num;
        cout << endl;
        if(num <= 1 || num > 5)
        cout << "Invalid number of players (2 - 5), please input again." << endl;
    }while (num <=1 || num > 5);
        
    //determine the each paly's number of coins at the beginning of the game
    int num_token;
    switch (num){
    case 2:
        num_token = 14;
        break;
    case 3:
        num_token = 11;
        break;
    case 4:
        num_token = 9;
        break;
    case 5:
        num_token = 8;
        break;
    default:
        break;
    }
        
    cout <<"Please set information for each player" << endl;
    for(int i = 0; i < num; ++i){
        cout << "**********Set information of Player No." << (i+1) << "**********"<< endl;
        string playerName;
        cout << "Pleas input the player name: ";
        cin >> playerName;
        cout << endl;
        cout << "Pleas input the troop's color: ";
        string armyColor;
        cin >> armyColor;
        cout << endl;
        cout << "Pleas input the player age: ";
        int playerAge;
        cin >> playerAge;
        cout << endl;
        //Player *p = new Player(playerName, armyColor, playerAge, num_token);
        players.push_back(new Player(playerName, armyColor, playerAge, num_token));
    }

    cout <<endl;
    cout << "Player infromation displayed below:" << endl;
    //1. set each player to interaction type
    //2. add observed players to observer
    //3. attach observer to each observable
    //4. display each player's information
    for(int i = 0; i < num; ++i){
        players.at(i)->setStrategy(0);
        obs->addObservablePlayer(players.at(i));
        players.at(i)->Attach(obs);
        players.at(i)->print();
    }
    //for(int i = 0; i < num; )
    
    //each player places 3 arimies at the beginning of the game
    cout << "Each player palces 3 armies at the begining of the game"<< endl;
    for(int i = 0; i < num; ++i){
        for(int j = 0; j < 3; ++j){
            players.at(i)->placeNewArmies(map);
        }
        players.at(i)->printCountries();
    }

    Deck *cards = mainLoop.shuffleAndDrawCards();
    //
    
    int turn = 0;
    do{
        for(int i = 0; i < num; ++i){
            cout << players.at(i)->getPlayerName() << ", please drive a card" <<endl;
            players.at(i)->chooseExchange_new2(cards);
        }
        turn ++;
    }while(turn <2);
    //moveLand method;
    cout<<"################# MoveArmies() #################" <<endl;
    players.at(0)->moveOverLand(map);
    players.at(0)->printCountries();
    cout << endl;cout << endl;

    cout<<"################# MoveOverLand and/or Water #################" <<endl;
    players.at(0)->moveOverLandAndWater(map);
    players.at(0)->printCountries();
    cout << endl;cout << endl;
        
    cout<<"################# BuildCity() #################" <<endl;
    players.at(0)->buildCity(map);
    cout << endl;
    players.at(0)->placeNewArmies(map);
    players.at(0)->printCountries();
    cout << endl;cout << endl;
        
    cout<<"################# BuildCity() #################" <<endl;
    if(!players.at(0)->ignore()){
        players.at(0)->buildCity(map);
        cout << endl;
        players.at(0)->placeNewArmies(map);
        players.at(0)->printCountries();
        cout << endl;cout << endl;
    }

    cout<<"################# DestroyArmy() #################" <<endl;
    if(!players.at(1)->ignore()){
        players.at(1)->destroyArmy(map, players);
        players.at(0)->printCountries();
        players.at(1)->printCountries();
        cout << endl;cout << endl;
    }
    cout<<"################# AndAction #################" <<endl;
    cout << players.at(1)->getPlayerName() << ", you can move an army and buid a city" <<endl;
    cout << "Fristly, move an army over land" <<endl;
    players.at(1)->moveOverLand(map);
    cout << "Then, build a city" << endl;
    players.at(1)->buildCity(map);
    cout << endl;cout << endl;
    
    cout<<"################# OrAction #################" <<endl;
    int select;
    cout << players.at(0)->getPlayerName()<< ", please select an anction: ";
    cout <<"1. Place a new army";
    cout <<"2. Move over Land ";
    cin >> select;
    if(select == 1){
        players.at(0)->placeNewArmies(map);
        players.at(0)->printCountries();
    }
    if(select == 2){
        players.at(0)->moveOverLand(map);
        players.at(0)->printCountries();
    }
    cout << endl;cout << endl;
    


    //release memory
    delete obs; obs = NULL;
    
    for(int i = 0; i < num; ++i){
        delete players.at(i);
        players.at(i) = NULL;
    }
    //delete players; players = NULL;
    string x;
    cin>>x;
    return 0; // end main function
}