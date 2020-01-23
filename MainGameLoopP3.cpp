#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "MapLoader.cpp"
#include "Player.cpp"
#include "BiddingRoom.cpp"
#include "Cards.cpp"
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
using namespace std;

class MainGameLoopP3{
    public:
    /* Select a map from a list of files as stored in a directory.
    *  Use the map loader to load the selected and appropriate map.
    */ 
    Graph* selectAndLoadMap() // will use this map in StartupPhase to load a map
    {
        
        cout << " Welcome to Eight Minute Empire Game" <<endl;
        cout << " Here are the maps you can choose" <<endl;
        // Read Maps Directory - Open directory
        struct dirent *entry;
        DIR *dir = opendir("/Users/chen/gitwork/new/Eight-Minute-Empire-game/MapsDirectory"); // hardcoded directory
        if (dir == NULL) 
        {
            // returns empty graph
            cout<< " Empty folder !!! "<< endl;
            return NULL;
        }
        // regex with wordOrNumber.map
        int m=0;
        vector<string> dirMapNames; 
        while ( (entry = readdir(dir)) != NULL ) 
        {
            if( std::regex_match(entry->d_name, std::regex("(^([\\w]+)(\\.map)$)") ) )// if file ends with .map it's good
            {
                cout << (m+1) << ": " << entry->d_name << endl;
                dirMapNames.push_back(entry->d_name);
                m++;
            }
        }
        closedir(dir); // CLOSE DIRECTORY

        // user selects an indexed map, and we obtain the name of the map
        int mapIndex;
        cout << "Please choose the Map-ID you want to play with: ";
        cin >> mapIndex;
        mapIndex--;
        // display selected map
        cout << "You have chosen to load map: "<< dirMapNames.at(mapIndex) << endl;

        // load the selected indexed map
        cout << "Loading " << dirMapNames.at(mapIndex) << " ..." << endl;


        // (1)create graph (2)read map (3)Validate map (4)print map
        int graphSize = 0;
        
        // count nodes in file.map
        ifstream infile;
        string line;
        infile.open(dirMapNames.at(mapIndex)); // OPEN selected file name
        
        while (std::getline(infile, line))
        {
            // count nodes (one node per line)
            graphSize++;
        }
        infile.close(); // CLOSE

        cout << "Creating graph of size " << graphSize << "..." << endl;
       
        // show the graph works ...
        Graph *graph = Graph::getInstance(graphSize);
        cout << "Graph *graph = Graph::getInstance(graphSize);" << endl;
        //cout << " dddddd"<< endl;
        bool valid = readMap(graph, dirMapNames.at(mapIndex));
        if(valid)
        {
            graph->printGraph();
        }
        else
        {
            printValidationError();
        }
        cout << endl;
        cout << endl;
        cout << "----------------------------------------------" <<endl;
        cout << endl;
        cout << endl;
        return graph;
    }

    //method creating players, and return as a vector
    vector <Player*> createPlayers(){
        vector<Player*> players;
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
        switch (num)
        {
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
        for(int i = 0; i < num; ++i){
            players.at(i)->print();
        }
        /*
        //Assign bidding facility to each player
        BiddingRoom *bid = new BiddingRoom();
        for (int i = 0; i < num ; ++i){
            players.at(i).playerBiddingRoom = bid;
        }
        */
        return players;
    }

    Player* chooseStartingPlayer(vector <Player*> players){
        //get the number of players
        int num = players.size();
        /*
        //create an array storing players
        Player *currentPlayers = new Player[num];
        for(int i = 0; i < players.size(); ++i){
            *(currentPlayers+i) = *players.at(i);
        }
        */
        BiddingRoom *bid = new BiddingRoom();
        Player* start = bid->startBidding_new(players, num);
        
        return start;
    }

    vector<Player*> determineOrder(){
        vector <Player*> players = createPlayers();
        Player *start = chooseStartingPlayer(players);
        int num = players.size();
        vector<Player*> allPlayers;
        //get the name
        string winnerStart = start->getPlayerName();
        //prompt the winner te decide who will be the first player
        cout << "[" << winnerStart <<"] won the bid, so you can choose who is the first player " <<endl;
        for(int i = 0 ; i < num ; ++i){
           cout << (i+1) <<". " << players.at(i)->getPlayerName() << endl;
        }
        int id;
        cout << "Please select the first player: ";
        cin >>id;
        string first = players.at(id-1)->getPlayerName();
        cout << first << " is the first player" << endl;

        //the index of the first player
        int k = id-1;
        do{
            //store the players into the new vector in clockwise order from the first player
            allPlayers.push_back(players.at(k++));
            //if k is equal to num, which means exceed the index bound
            //reset it to 0
            if(k == num){
                k=0;
            }
        //when k is equal to the index of the first player, terminates the loop
        }while(k != id-1);

        cout<<endl;cout<<endl;
        cout << "The game will go in the clockwise order: " <<endl;
        for(int i = 0; i < num; i++){
            //cout << (i+1) <<". " << allPlayers.at(i)->getPlayerName() << endl;
            allPlayers.at(i)->print();
        }
        return allPlayers;
    }

    /* Shuffling the cards of the deck, and draw() 6 cards, 
    *  that will be put face up along the top of the board.
    */
    Deck* shuffleAndDrawCards()
    {
        Deck *gameDeck = new Deck();
        /*
        // show deck of cards before shuffling ...
        cout << "Deck of cards: " << endl;
        for (int i = 0; i < gameDeck.deck.size(); i++)
        {
            cout << "card from deck: #" << (i+1) << endl;
            cout << gameDeck.deck.at(i).getAction() << endl;
            cout << gameDeck.deck.at(i).getGood() << endl;
        }
        */
        // shuffle
        cout << "The cards are being shuffled by a shuffle master ..."<< endl;
        // Initialize random
        srand(time(NULL));
        int randIndex;
        Card cardHolder = Card();
        for (int i = 0; i < gameDeck->deck.size(); i++)
        {
            randIndex = (rand() % 42); // index range: [0-41]
            cardHolder = gameDeck->deck.at(randIndex); // holds the randomIndexedCard

            // swap positions of the 2 cards, indexed: 'i' and 'randIndex'
            gameDeck->deck.at(randIndex) = gameDeck->deck.at(i);
            gameDeck->deck.at(i) = cardHolder;
        }
        /*
        // show deck of cards after shuffling ...
        cout << "Deck of cards (after shuffling): " << endl;
        for (int i = 0; i < gameDeck.deck.size(); i++)
        {
            cout << "card from deck: #" << (i+1) << endl;
            cout << gameDeck.deck.at(i).getAction() << endl;
            cout << gameDeck.deck.at(i).getGood() << endl;
        }
        */
        // draw 6 cards, that will be placed in 'cardsSpace' next to the deck
        cout << "Drawing 6 cards into the cards space ..." << endl;
        for (int i = 0; i < 6; i++)
        {
            gameDeck->draw();
        }

        // print 'cardSpace' of the current gameDeck ...
        for (int i = 0; i < 6; i++)
        {
            cout<< "Card in cardSpace position "<< i << ":" << endl;
            cout<< gameDeck->cardSpace.at(i).getAction() << endl;
            cout<< gameDeck->cardSpace.at(i).getGood() << endl;
        }
        return gameDeck;
    }

    void mainGame(){
        //load map
        Graph *map = selectAndLoadMap();
        //*map;
        //map = &graph;
        //get the plays
        vector<Player*> players = determineOrder();
        //get the number of players
        int num = players.size();
        //a boolean array to store the state of each player
        //if one player have the maximal number of cards or no coins, changes his/her state to true
        bool *states = new bool[num];
        int maxCards;
        if(num == 2){
            maxCards = 13;
        }
        if(num == 3){
            maxCards = 10;
        }
        if(num == 4){
            maxCards = 8;
        }
        if(num == 5){
            maxCards = 7;
        }



        Deck *cards = shuffleAndDrawCards();
        int turn = 0;
        bool overFlag = true;
        do{
            for(int i = 0 ; i < num; ++i){
                /*
                //check the player state before take actions
                //if the state is true, break the for loop
                if(states[i] == true){
                    break;
                }
                */
               
                cout << players.at(i)->getPlayerName() << ", please drive a card." <<endl;
                string action = players.at(i)->chooseExchange_new(cards);
                cout << "Action: " << action << endl;
                players.at(i)->print();
                cout <<endl;cout <<endl;
                //check the player state
                if(players.at(i)->getNumOfCards() == maxCards || players.at(i)->getNumOfTokens() == 0){
                    states[i] = true;
                    cout << players.at(i)->getPlayerName() << ", you cannot continue the game since you do not have coins or have the maximal number of cards" << endl;
                }


                for(int k = 0; k < num; ++k){
                    overFlag = overFlag && states[k]; 
                }
            }
            turn++;
        }while(turn < 2); // the condition should be !overFlag
    }

    void playerActionTest(){
          //load map
        Graph *map = selectAndLoadMap();
        //*map;
        //map = &graph;
        //get the plays
        vector<Player*> players = determineOrder();
        cout<<endl;cout<<endl;
        //get the number of players
        int num = players.size();
        //a boolean array to store the state of each player
        //if one player have the maximal number of cards or no coins, changes his/her state to true
        cout << "Each player palces 3 armies at the begining of the game"<< endl;
        for(int i = 0; i < num ; i++){
            //at the beginning, each player places 3 armies in the starting region
            for(int j = 0; j < 3; j++){
                players.at(i)->placeNewArmies(map);
            }
            players.at(i)->printCountries();
        }
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
    }



};