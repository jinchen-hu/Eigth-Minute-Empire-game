
#include "GameStart.cpp"

int main()
{
    GameStart startgame = GameStart();

    // these respectively return the game objects: Map, Players, and Cards
    startgame.selectAndLoadMap();
    startgame.createPlayers();
    startgame.createCards();

    return 0;
}