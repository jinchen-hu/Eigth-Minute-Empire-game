
#include <iostream>
#include <string> 
#include <cstdlib>
#include <vector>

#include "GameStart.cpp"

using namespace std;

class StartupPhase
{
public:    
    
    /* Shuffling the cards of the deck, and draw() 6 cards, 
    *  that will be put face up along the top of the board.
    */
    void shuffleAndDrawCards()
    {
        Deck gameDeck = Deck();

        // show deck of cards before shuffling ...
        cout << "Deck of cards: " << endl;
        for (int i = 0; i < gameDeck.deck.size(); i++)
        {
            cout << "card from deck: #" << (i+1) << endl;
            cout << gameDeck.deck.at(i).getAction() << endl;
            cout << gameDeck.deck.at(i).getGood() << endl;
        }

        // shuffle
        cout << "The cards are being shuffled by a shuffle master ..."<< endl;
        // Initialize random
        srand(time(NULL));
        int randIndex;
        Card cardHolder = Card();
        for (int i = 0; i < gameDeck.deck.size(); i++)
        {
            randIndex = (rand() % 42); // index range: [0-41]
            cardHolder = gameDeck.deck.at(randIndex); // holds the randomIndexedCard

            // swap positions of the 2 cards, indexed: 'i' and 'randIndex'
            gameDeck.deck.at(randIndex) = gameDeck.deck.at(i);
            gameDeck.deck.at(i) = cardHolder;
        }

        // show deck of cards after shuffling ...
        cout << "Deck of cards (after shuffling): " << endl;
        for (int i = 0; i < gameDeck.deck.size(); i++)
        {
            cout << "card from deck: #" << (i+1) << endl;
            cout << gameDeck.deck.at(i).getAction() << endl;
            cout << gameDeck.deck.at(i).getGood() << endl;
        }

        // draw 6 cards, that will be placed in 'cardsSpace' next to the deck
        cout << "Drawing 6 cards into the cards space ..." << endl;
        for (int i = 0; i < 6; i++)
        {
            gameDeck.draw();
        }

        // print 'cardSpace' of the current gameDeck ...
        for (int i = 0; i < 6; i++)
        {
            cout<< "Card in cardSpace position "<< i << ":" << endl;
            cout<< gameDeck.cardSpace.at(i).getAction() << endl;
            cout<< gameDeck.cardSpace.at(i).getGood() << endl;
        }
    }

    /* Each player takes a set of one color of cubes (14 armies) and discs (3 cities). 
    *  Each player places 3 armies on the starting region on the board. 
    *  If playing with 2 players, each player takes turns placing one army at a time of a third, 
    *  non-player color in any region on the board UNTIL ten armies have been placed.
    */
    void playersPlacingOnMap()
    {
        GameStart startgame = GameStart();

        // it loads the map that the user chooses
        Graph map = startgame.selectAndLoadMap();

        // The players brought from StartGame have random names, armyColors, 
        // and a SPECIFIC number of tokens depending on the number of players
        vector<Player> players = startgame.createPlayers();

        // armyColor is already given, but assign the 14 armies and 3 cities to each player
        cout << "Players taking cubes(14 armies) and discs (3 cities) ..." << endl;
        for (int i = 0; i < players.size(); i++)
        {
            players.at(i).setNumOfArmies(14);
            players.at(i).setNumOfCities(3);
        }
        
        // If more than 2 players, each player places 3 armies on the starting region on the board
        if(players.size() > 2)
        {
            // starting region may be any country
            cout<< "Each player takes turns placing one army at a time (each places 3 armies)" << endl;

            // each player places 3 armies on the starting region on the board
            for (int i = 0; i < players.size(); i++)
            {
                cout << players.at(i).getPlayerName() << ": " << endl;
                cout << "Placing 3 armies on the Starting Region ..." << endl;
                
                players.at(i).addCountryOccupied(map.arr[0].country, 3, 0);
                map.arr[0].country->addPlayerInCountry(&players.at(i), 3, 0);
            }
            
        }
        // unless we have 2 players
        if(players.size() == 2)
        {
            // take turns
            cout<< "Each player takes turns placing one army at a time (until each player reaches 10)" << endl;

            Player mockPlayer = Player("MockPlayer", "black", 100, 100);

            int count = 0;
            while(count < 10)
            {
                cout<< "Place non-playing-colored armies (mockPlayer): "<< endl;
                mockPlayer.placeNewArmies(map);
                
                for (int i = 0; i < players.size(); i++)
                {
                    cout << players.at(i).getPlayerName() << ": " << endl;
                    players.at(i).placeNewArmies(map);
                }

                count++;
            }
        }   

        // JUST FOR THE DRIVER SHOW, OUTPUT PLAYER AND GRAPH INFO ...
        cout << "INFO ABOUT THE PLAYERS AND THE MAP AFTER BEING POPULATED: " << endl;
        for (int i = 0; i < players.size(); i++)
        {
            cout << "**** Player: " << players.at(i).getPlayerName() << " ****" << endl;
            cout << players.at(i).getPlayerName() << " has #coins: "<< players.at(i).getNumOfTokens() << endl;
            cout << "Countries Occupied: " << endl;

            for (int k = 0; k < players.at(i).countriesOccupied.size(); k++)
            {
                cout << players.at(i).countriesOccupied.at(k).country->getName() << endl;
                cout << players.at(i).countriesOccupied.at(k).numberArmies << " Armies" << endl;
                cout << players.at(i).countriesOccupied.at(k).numberCities << " Cities" << endl;
            }
        }

        // JUST FOR THE DRIVER SHOW, user the vector 'players' and call biddingFacility
        Player winnerStart;
        winnerStart = chooseStartingPlayer(players);

        // check I have it
        cout << "WASUP " << winnerStart.getPlayerName() << " you decide who starts the game" << endl;
    }

    /* There is only one bid per game.
    *  Using biddingRoom
    */
    Player chooseStartingPlayer( vector <Player> allPlayers )
    {
        // this sucks, but yeah ...
        Player currentPlayers[ allPlayers.size() ];
        for (int i = 0; i < allPlayers.size(); i++)
        {
            currentPlayers[i] = allPlayers.at(i);
        }

        BiddingRoom *biddingRoom = new BiddingRoom(); //in heap
        for (int i = 0; i < allPlayers.size(); i++)
        {
            currentPlayers[i].playerBiddingRoom = biddingRoom; // in heap
        }

        // startBidding returns the winning Player
        Player startPlayer;
        startPlayer = currentPlayers[0].playerBiddingRoom->startBidding(currentPlayers, allPlayers.size());

        return startPlayer;
    }

    
};
