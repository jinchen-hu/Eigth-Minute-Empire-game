
#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include "MapLoader.cpp"
#include "Player.cpp"
#include "BiddingRoom.cpp"
#include "Cards.cpp"

#include <fstream>

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>

using namespace std;

/*  //Form of struct
    struct dirent{
        ino_t d_ino; // inode number 
        off_t d_off; // offset to the next dirent 
        unsigned short d_reclen; // length of this record 
        unsigned char d_type; // type of file 
        char d_name[256]; // filename 
    };
*/

// GameStart 
class GameStart
{   
    public:
    
    /* Select a map from a list of files as stored in a directory.
    *  Use the map loader to load the selected and appropriate map.
    */ 
    Graph selectAndLoadMap() // will use this map in StartupPhase to load a map
    {
        cout << "Select a map from the following directory (enter an index number): " << endl;

        // Read Maps Directory - Open directory
        struct dirent *entry;
        DIR *dir = opendir("/Users/Celestino/Desktop/Eight-Minute-Empire-game"); // hardcoded directory
        if (dir == NULL) 
        {
            // returns empty graph
            Graph emptyGraph = Graph();
            return emptyGraph;
        }
        // regex with wordOrNumber.map
        int m=0;
        vector<string> dirMapNames; 
        while ( (entry = readdir(dir)) != NULL ) 
        {
            if( std::regex_match(entry->d_name, std::regex("(^([\\w]+)(\\.map)$)") ) )// if file ends with .map it's good
            {
                cout << m << ": ";
                cout << entry->d_name << endl;
                
                dirMapNames.push_back(entry->d_name);

                m++;
            }
        }
        closedir(dir); // CLOSE DIRECTORY

        // user selects an indexed map, and we obtain the name of the map
        int mapIndex;
        cin >> mapIndex;

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
        Graph *graph = createGraph(graphSize);
        bool valid = readMap(graph, dirMapNames.at(mapIndex));
        if(valid)
        {
            printGraph(graph);
        }
        else
        {
            printValidationError();
        }
        return *graph;
    }

    /* Create all the players, assign biding facility to the players
    */
    vector <Player> createPlayers() // returns array of players
    {
        cout << "Select the number of players in the game (2-5 players): " << endl;
        
        int numPlayers;
        cin >> numPlayers;
        cout << numPlayers;

        // 5 colours and ages, for 5 possible players (HARDCODED - NO SPECIFICATIONS)
        string colors[] = {"blue", "green", "red", "yellow", "white"};
        int ages[] = {20, 23, 24, 20, 30};
        
        // create the players, assign a name, a color, an age, and a number of tokens (SPECIFIED)
        // if playing with five players, each player takes 8 coins
        // if playing with four players, each player takes 9 coins
        // if playing with three players, each player takes 11 coins
        // if playing with two players, each player takes 14 coins.
        int tokens;
        if(numPlayers == 2)
        {
            tokens = 14;
        }
        if(numPlayers == 3)
        {
            tokens = 11;
        }
        if(numPlayers == 4)
        {
            tokens = 9;
        }
        if(numPlayers == 5)
        {
            tokens = 8;
        }
             
        // create the players, assign a name, a color, an age, and a number of tokens (ACCORDING to the number of players)
        vector<Player> players;
        for (size_t i = 0; i < numPlayers; i++)
        {
            string name = "player" + std::to_string(i);
            players.push_back( Player(name, colors[i], ages[i], tokens) );

            cout << players.at(i).getPlayerName() << endl;
        }
        
        // assign bidding facility to each player
        BiddingRoom *biddingRoom = new BiddingRoom(); //in heap
        for (int i = 0; i < numPlayers; i++)
        {
            players.at(i).playerBiddingRoom = biddingRoom; // in heap
        }
        
        // show players and their hands ...
        for (int i = 0; i < numPlayers; i++)
        {   
            cout <<  "player name: " << players.at(i).getPlayerName() << endl;
            
            if (players.at(i).playerHand.size() > 0)
            {
                // iterate and show the player's hand
                for (int k = 0; i < players.at(i).playerHand.size(); k++)
                {
                    cout << "card from player's hand:" << endl;
                    cout << "action: " << players.at(i).playerHand.at(k).getAction() << endl;
                    cout << "good: " << players.at(i).playerHand.at(k).getGood() << endl;
                }
            }
            else
            {
                cout << "The player's hand is empty" << endl;
            }
        }
        return players;
    }
    
    /* create a deck of cards, and return it
    *  and assign an empty hand of cards to each player (redundant, since each player already has empty deck)
    */
    Deck createCards() // returns card deck
    {
        // create a deck of cards
        // each player already has an empty hand, so no need to assign empty hand to each player ... (EXPLAIN IN DEMO)
        Deck deckObject = Deck();
    
        // show deck of cards ...
        cout << "Deck of cards: " << endl;
        for (int i = 0; i < deckObject.deck.size(); i++)
        {
            cout << "card from deck: #" << (i+1) << endl;
            cout << deckObject.deck.at(i).getAction() << endl;
            cout << deckObject.deck.at(i).getGood() << endl;
        }

        return deckObject;
    }

};

