
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "MapLoader.cpp"
#include "BiddingRoom.cpp"
#include "StatisticsObserver.cpp"
using namespace std;

//load the map
Graph *generateMap()
{
    cout << " Welcome to Eight Minute Empire Game" << endl;
    cout << " Here are the maps you can choose" << endl;
    // Read Maps Directory - Open directory
    struct dirent *entry;
    DIR *dir = opendir("./MapsDirectory"); // hardcoded directory
    if (dir == NULL)
    {
        // returns empty graph
        cout << " Empty folder !!! " << endl;
        return 0;
    }
    // regex with wordOrNumber.map
    int m = 0;
    vector<string> dirMapNames;
    while ((entry = readdir(dir)) != NULL)
    {
        if (std::regex_match(entry->d_name, std::regex("(^([\\w]+)(\\.map)$)"))) // if file ends with .map it's good
        {
            cout << (m + 1) << ": " << entry->d_name << endl;
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
    cout << "You have chosen to load map: " << dirMapNames.at(mapIndex) << endl;

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
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "Graph *graph = Graph::getInstance();" << endl;
    cout << endl;
    // show the graph works ...
    Graph *graph = Graph::getInstance(graphSize);
    //cout << " dddddd"<< endl;
    bool valid = readMap(graph, dirMapNames.at(mapIndex));
    if (valid)
    {
        graph->printGraph();
    }
    else
    {
        printValidationError();
    }
    cout << endl;
    cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << endl;

    return graph;
}
Graph *generateMapComputer()
{
    cout << " Welcome to Eight Minute Empire Game" << endl;
    cout << " Here are the maps you can choose" << endl;
    // Read Maps Directory - Open directory
    struct dirent *entry;
    DIR *dir = opendir("./MapsDirectory"); // hardcoded directory
    if (dir == NULL)
    {
        // returns empty graph
        cout << " Empty folder !!! " << endl;
        return 0;
    }
    // regex with wordOrNumber.map
    int m = 0;
    vector<string> dirMapNames;
    while ((entry = readdir(dir)) != NULL)
    {
        if (std::regex_match(entry->d_name, std::regex("(^([\\w]+)(\\.map)$)"))) // if file ends with .map it's good
        {
            cout << (m + 1) << ": " << entry->d_name << endl;
            dirMapNames.push_back(entry->d_name);
            m++;
        }
    }
    closedir(dir); // CLOSE DIRECTORY

    // user selects an indexed map, and we obtain the name of the map
    int mapIndex;
    cout << "Please choose the Map-ID you want to play with: ";
    // cin >> mapIndex;
    // mapIndex--;
    mapIndex = 0;
    // display selected map
    cout << "You have chosen to load map: " << dirMapNames.at(mapIndex) << endl;

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
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << endl;
    cout << "Graph *graph = Graph::getInstance();" << endl;
    cout << endl;
    // show the graph works ...
    Graph *graph = Graph::getInstance(graphSize);
    //cout << " dddddd"<< endl;
    bool valid = readMap(graph, dirMapNames.at(mapIndex));
    if (valid)
    {
        graph->printGraph();
    }
    else
    {
        printValidationError();
    }
    cout << endl;
    cout << endl;
    cout << "----------------------------------------------" << endl;
    cout << endl;
    cout << endl;

    return graph;
}

//create deck
Deck *createDeck()
{
    cout << endl;
    cout << "=================================Loading Deck=================================" << endl;
    cout << endl;
    Deck *d = new Deck();
    d->printDeck();
    cout << endl;
    cout << endl;
    d->generateTop();
    cout << endl;
    return d;
}
Player *determineWinner(vector<Player *> players, Graph *graph)
{
    int score;
    Player *winner = players.at(0);
    for (int i = 0; i < players.size(); i++)
    {
        score = players.at(i)->computeScore2(players, graph);
        cout << players.at(i)->getPlayerName() << ": " << score << "\n";
        if ((score > winner->computeScore2(players, graph)))
            winner = players.at(i);
        else if (score == winner->computeScore2(players, graph))
        {
            if (players.at(i)->getNumOfTokens() == winner->getNumOfTokens())
            {
                if (players.at(i)->getNumOfArmies() == winner->getNumOfArmies())
                {
                    if (players.at(i)->getNumOfControlledCountries() > winner->getNumOfControlledCountries())
                        winner = players.at(i);
                }
                else if (players.at(i)->getNumOfArmies() > winner->getNumOfArmies())
                {
                    winner = players.at(i);
                }
            }
            else if (players.at(i)->getNumOfTokens() > winner->getNumOfTokens())
            {
                winner = players.at(i);
            }
        }
    }
    return winner;
}

//set the players
vector<Player *> createPlayers()
{
    //create a vector storing players
    vector<Player *> players;
    //declare the observer
    StatisticsObserver *obs = new StatisticsObserver();
    //set each player's information
    int num;
    do
    {
        cout << "Please set the number of players (2 to 4): ";
        cin >> num;
        cout << endl;
        if (num <= 1 || num > 5)
            cout << "Invalid number of players (2 - 4), please input again." << endl;
    } while (num <= 1 || num > 5);

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

    cout << "Please set information for each player" << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << "**********Set information of Player No." << (i + 1) << "**********" << endl;
        string playerName;
        cout << "Please input the player name: ";
        cin >> playerName;
        cout << endl;
        cout << "Please input the troop's color: ";
        string armyColor;
        cin >> armyColor;
        cout << endl;
        cout << "Please input the player age: ";
        int playerAge;
        cin >> playerAge;
        cout << endl;
        cout << "What strategy do you want for this player?" << endl;
        int strat = 0;
        cout << "1. Interactive " << endl;
        cout << "2. Greedy " << endl;
        cout << "3. Moderate " << endl;
        cin >> strat;
        strat--;

        Player *p = new Player(playerName, armyColor, playerAge, num_token);
        p->setStrategy(strat);
        players.push_back(p);
    }

    cout << endl;
    cout << "Player infromation displayed below:" << endl;
    //1. set each player to interaction type
    //2. add observed players to observer
    //3. attach observer to each observable
    //4. display each player's information
    for (int i = 0; i < num; ++i)
    {
        obs->addObservablePlayer(players.at(i));
        players.at(i)->Attach(obs);
        players.at(i)->print();
    }
    return players;
}

vector<Player *> createPlayersComputer()
{
    //create a vector storing players
    vector<Player *> players;
    //declare the observer
    StatisticsObserver *obs = new StatisticsObserver();
    //set each player's information
    int num;
    do
    {
        cout << "Please set the number of players (2 to 4): " << endl;
        //cin >> num;
        //randomize number of players
        num = (rand() % 3) + 2;
        num--;
        cout << num<< endl;
        if (num <= 1 || num > 5)
            cout << "Invalid number of players (2 - 4), please input again." << endl;
    } while (num <= 1 || num > 5);

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
    //string colors[] = {"Green","Red","Blue","Black"};
    vector<string> colors;
    colors.push_back("Green");
    colors.push_back("Red");
    colors.push_back("Blue");
    colors.push_back("Black");
    int colorIndex;
    cout << "Please set information for each player" << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << "**********Set information of Player No." << (i + 1) << "**********" << endl;
        string playerName;
        cout << "Please input the player name: ";
        playerName = "Player" + to_string(i);
        cout << endl;
        cout << "Please input the troop's color: ";
        string armyColor;
        //cin >> armyColor;
        //Get random color and remove it from options
        colorIndex = rand() % colors.size();
        armyColor = colors.at(colorIndex);
        colors.erase(colors.begin() + colorIndex);
        cout << endl;
        cout << "Please input the player age: ";
        int playerAge;
        //cin >> playerAge;
        playerAge = rand() % 100 + 2;
        cout << endl;
        cout << "What strategy do you want for this player?" << endl;
        int strat = 0;
        cout << "1. Interactive " << endl;
        cout << "2. Greedy " << endl;
        cout << "3. Moderate " << endl;
        strat = rand() % 2 + 1;

        Player *p = new Player(playerName, armyColor, playerAge, num_token);
        p->setStrategy(strat);
        players.push_back(p);
    }

    cout << endl;
    cout << "Player infromation displayed below:" << endl;
    //1. set each player to interaction type
    //2. add observed players to observer
    //3. attach observer to each observable
    //4. display each player's information
    for (int i = 0; i < num; ++i)
    {
        obs->addObservablePlayer(players.at(i));
        players.at(i)->Attach(obs);
        players.at(i)->print();
    }
    return players;
}

Player *chooseStartingPlayer(vector<Player *> players)
{
    int num = players.size();
    BiddingRoom *bid = new BiddingRoom();
    Player *start = bid->startBidding_new(players, num);
    return start;
}

vector<Player *> determineOrder()
{
    //get the players set
    vector<Player *> players = createPlayers();
    //get the bidding winner
    Player *start = chooseStartingPlayer(players);
    int num = players.size();
    vector<Player *> allPlayers;
    //get the name
    string winnerStart = start->getPlayerName();
    //prompt the winner te decide who will be the first player
    cout << "[" << winnerStart << "] won the bid, so you can choose who is the first player " << endl;
    for (int i = 0; i < num; ++i)
    {
        cout << (i + 1) << ". " << players.at(i)->getPlayerName() << endl;
    }
    int id;
    cout << "Please select the first player: ";
    cin >> id;
    string first = players.at(id - 1)->getPlayerName();
    cout << first << " is the first player" << endl;

    //the index of the first player
    int k = id - 1;
    do
    {
        //store the players into the new vector in clockwise order from the first player
        allPlayers.push_back(players.at(k++));
        //if k is equal to num, which means exceed the index bound reset it to 0
        if (k == num)
        {
            k = 0;
        }
        //when k is equal to the index of the first player, terminates the loop
    } while (k != id - 1);

    cout << endl;
    cout << endl;
    cout << "The game will go in the clockwise order: " << endl;
    for (int i = 0; i < num; i++)
    {
        cout << (i + 1) << ". ";
        allPlayers.at(i)->print();
    }
    return allPlayers;
}
vector<Player *> determineOrderComputer()
{
    //get the players set
    vector<Player *> players = createPlayersComputer();

    cout << endl;
    cout << endl;
    cout << "The game will go in the clockwise order: " << endl;
    for (int i = 0; i < players.size(); i++)
    {
        cout << (i + 1) << ". ";
        players.at(i)->print();
    }
    return players;
}
