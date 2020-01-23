#include <iostream>
#include <string>
#include "CardsFactory.cpp"
//#include "Player.cpp"
#include "Helper.cpp"
using namespace std;

int main(){
    /*
    Graph *map = generateMap();
    Deck *d = createDeck();
    vector<Player*> pls = determineOrder();
    for(int i = 0; i < pls.size(); ++i){
        for(int j = 0; j < 3; ++j){
            pls.at(i)->placeNewArmies(map);
        }
    }
    for(int i = 0; i < 10; ++i){
        (pls.at(i)->chooseExchange(d))->takeActions(pls.at(i),map, pls);
    }
    Deck *d = createDeck();*/

    
    for(int i = 0; i < 21; ++i){
        Card *card = CardsFactory::CreateCard(i);
        cout << *card << endl;
    }

    return 0;
}
