#include "Cards.cpp"
#include "Player.cpp"

int main()
{
    Deck deck;
    vector<Player> players =  { Player("Tino","blue",25,10),
                                Player("Brenden","green",22,10),
                                Player("Tahar","red",22,10),
                                Player("Jinchen","purple",21,10)};

    deck.draw();
    deck.draw();
    deck.draw();
    deck.draw();
    deck.draw();
    deck.draw();
    int player =0;
    while(true){
        cout << players.at(player).getPlayerName() << " YOUR TURN!" << endl;
        players.at(player).chooseExchange(&deck);
        if(players.at(player).getNumOfCards() > 8)
            break;
        player = ((player + 1)%players.size());
    }

    
    return 0;
}