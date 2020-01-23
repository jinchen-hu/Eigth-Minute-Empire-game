// BiddingRoom.cpp file
#include <iostream>
#include <string>
#include <vector>
#include "BiddingRoom.h"

using namespace std;

// Implementation of BiddingRoom.h 
BiddingRoom::~BiddingRoom()
{
    std::cout << "destructor called for BiddingRoom" << endl;

    // not on heap, so I dont need to deallocate
    //delete ptrPlayers;
}

// Bidding occurs here
Player BiddingRoom::startBidding(Player currentPlayers[], int size)
{   
    //cout << "-- Welcome to Eight-Minute Empire Game --" << endl;
    cout << "To begin the game, all players must bid a certain amount of coins." << endl;
    cout << endl;
    biddingValuesOfPlayers = new int[size];
    // get the bids
    for (int i = 0; i < size; i++)
    {
        cout << "Player " << currentPlayers[i].getPlayerName() << endl;
        cout << "Privately choose number to bid: ";
        int x;
        cin >> x;
        biddingValuesOfPlayers[i]=x;
        //currentPlayers[i].payCoins(5);
        cout << endl;
    }
    // reveal the bids of each player
    cout << "All players reveal their bids at the same time: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Player " << currentPlayers[i].getPlayerName() << " bidded " << biddingValuesOfPlayers[i] << endl;
    }
    
    // Operations to determine who won ...
    bool allEqual = false;
    int num = 0;
    for (int i = 0; i < (size-1); i++)
    {
        if(biddingValuesOfPlayers[i] == biddingValuesOfPlayers[i+1])
        {
            num++;
        }
    }

    // index of winner
    int index = 0;
    // If they all have the same bid, then we choose the youngest player
    if(num == (size-1))
    { 
        Player youngest;

        int min = currentPlayers[0].getPlayerAge();
        for (int i = 1; i < size; i++)
        {   
            if(currentPlayers[i].getPlayerAge() < min)
            {
                min = currentPlayers[i].getPlayerAge();
                index = i;
            }
        }
        // assign reference to the pointer
        youngest = currentPlayers[index];
        
        // results
        cout << "All the players' bids were equal. " << endl;
        cout << "The youngest player is: " << youngest.getPlayerName() << endl;

        // youngest player pays the coins...
        if(biddingValuesOfPlayers[index]<= youngest.getNumOfTokens() )
        {
            cout << "The player has enough tokens: " << youngest.getNumOfTokens() << endl;
            youngest.payCoins(biddingValuesOfPlayers[index]);// pay the coins
            cout << youngest.getPlayerName() + " has " << youngest.getNumOfTokens() << " tokens remaining." << endl;
        }       

        // after paying, choose whos starts.
        cout << youngest.getPlayerName() << " chooses who will play first." << endl;
        return youngest;

    }
    else // otherwise choose the highest bid
    {
        Player maxBidder;

        int max = biddingValuesOfPlayers[0];
        for (int i = 1; i < size; i++)
        {
            if(biddingValuesOfPlayers[i] > max)
            {
                max = biddingValuesOfPlayers[i];
                index = i;
            }
        }
        // assign reference to the pointer
        maxBidder = currentPlayers[index];
    
        // results
        cout << "The player with the biggest bid is: " + maxBidder.getPlayerName() << endl;
        
        // maxBidder pays the coins
        
        if(biddingValuesOfPlayers[index]<= maxBidder.getNumOfTokens() )
        {
            cout << "The player has enough tokens: " << maxBidder.getNumOfTokens() << endl;
            maxBidder.payCoins(biddingValuesOfPlayers[index]);// pay the coins
            cout << maxBidder.getPlayerName() + " has " << maxBidder.getNumOfTokens() << " tokens remaining." << endl;
        }   
        
        // after paying
        cout<< maxBidder.getPlayerName() + " chooses who will play first." << endl;
        return maxBidder;
    }
}


Player* BiddingRoom::startBidding_new(vector<Player*> players, int size){   
    //cout << "-- Welcome to Eight-Minute Empire Game --" << endl;
    cout << "To begin the game, all players must bid a certain amount of coins." << endl;
    cout << endl;
    biddingValuesOfPlayers = new int[size];
    // get the bids
    for (int i = 0; i < size; i++)
    {
        cout << "Player " << players.at(i)->getPlayerName() << endl;
        cout << "Privately choose number to bid: ";
        int x;
        cin >> x;
        biddingValuesOfPlayers[i]=x;
        //players.at(i)->payCoins(x);
        cout << endl;
    }
    // reveal the bids of each player
    cout << "All players reveal their bids at the same time: " << endl;
    for (int i = 0; i < size; i++)
    {
        cout << "Player " << players.at(i)->getPlayerName() << " bidded " << biddingValuesOfPlayers[i] << endl;
    }
    
    // Operations to determine who won ...
    bool allEqual = false;
    int num = 0;
    for (int i = 0; i < (size-1); i++)
    {
        if(biddingValuesOfPlayers[i] == biddingValuesOfPlayers[i+1])
        {
            num++;
        }
    }

    // index of winner
    int index = 0;
    // If they all have the same bid, then we choose the youngest player
    if(num == (size-1))
    { 
        Player *youngest;

        int min = players.at(0)->getPlayerAge();
        for (int i = 1; i < size; i++)
        {   
            if(players.at(i)->getPlayerAge() < min)
            {
                min = players.at(i)->getPlayerAge();
                index = i;
            }
        }
        // assign reference to the pointer
        youngest = players.at(index);
        
        // results
        cout << "All the players' bids were equal. " << endl;
        cout << "The youngest player is: " << youngest->getPlayerName() << endl;

    
        // youngest player pays the coins...
        if(biddingValuesOfPlayers[index]<= youngest->getNumOfTokens() )
        {
            cout << "The player has enough tokens: " << youngest->getNumOfTokens() << endl;
            youngest->payCoins(biddingValuesOfPlayers[index]);// pay the coins
            cout << youngest->getPlayerName() + " has " << youngest->getNumOfTokens() << " tokens remaining." << endl;
        }       
        
        // after paying, choose whos starts.

        cout << youngest->getPlayerName() << " chooses who will play first." << endl;
        return youngest;

    }
    else // otherwise choose the highest bid
    {
        Player* maxBidder;

        int max = biddingValuesOfPlayers[0];
        for (int i = 1; i < size; i++)
        {
            if(biddingValuesOfPlayers[i] > max)
            {
                max = biddingValuesOfPlayers[i];
                index = i;
            }
        }
        // assign reference to the pointer
        maxBidder = players.at(index);
    
        // results
        cout << "The player with the biggest bid is: " + maxBidder->getPlayerName() << endl;
        
        // maxBidder pays the coins
        
        if(biddingValuesOfPlayers[index]<= maxBidder->getNumOfTokens() )
        {
            cout << "The player has enough tokens: " << maxBidder->getNumOfTokens() << endl;
            maxBidder->payCoins(biddingValuesOfPlayers[index]);// pay the coins
            cout << maxBidder->getPlayerName() + " has " << maxBidder->getNumOfTokens() << " tokens remaining." << endl;
        }   
        
        // after paying
        cout<< maxBidder->getPlayerName() + " chooses who will play first." << endl;
        return maxBidder;
    }
}


