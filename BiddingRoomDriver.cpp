// This is the BiddingRoomDriver.cpp
#include <iostream>
#include <string>
#include "BiddingRoom.cpp"
#include "Player.cpp"

using namespace std;

int main()
{
    // create 4 Players
    Player currentPlayers[] = { Player("Tino","blue",25,10),
                                Player("Brenden","green",22,10),
                                Player("Tahar","red",22,10),
                                Player("Jinchen","purple",21,10)};

    int size = sizeof(currentPlayers)/sizeof(currentPlayers[0]);

    BiddingRoom *biddingRoom = new BiddingRoom(); //in heap

    for (int i = 0; i < size; i++)
    {
        currentPlayers[i].playerBiddingRoom = biddingRoom; // in heap
    }

    currentPlayers[0].playerBiddingRoom->startBidding(currentPlayers, size);
    // *(currentPlayers[0].playerBiddingRoom).startBidding(...);
    

    //end
    return 0;
}