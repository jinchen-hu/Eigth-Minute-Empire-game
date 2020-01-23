// BiddingRoom.h file
#ifndef BIDDINGROOM_H
#define BIDDINGROOM_H 

#include <iostream>
#include "Player.h"
#include <vector>
using namespace std;

class BiddingRoom
{
    private:
        int * biddingValuesOfPlayers; 

    public:
        ~BiddingRoom(); // need destructor, to deallocate memory of pointer in class
        Player startBidding(Player currentPlayers[], int size); // initializes the biddingValuesOfPlayers[], and chooses a wining player
        Player* startBidding_new(vector<Player*> players, int size);
};

#endif