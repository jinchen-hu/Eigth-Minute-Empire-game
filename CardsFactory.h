#ifndef CARDSFACTORY
#define CARDSFACTORY
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>
#include "Player.h"

using namespace std;

class Player;
/* done
add exchange() method -- 
    pure virtual method
    return the pointer of card object 
TODO
add takeAction()method -- 
    pure virtual method
    receive the player object that is drew the card right now
    according to the card action prompting
    the player taking different actions (including quantities)

*/
class Card
{
protected:
    int *id;
    string *good, *action;

public:
    virtual ~Card();
    //Card(int id, string good, string action);
    void setGood(string s);
    inline string getGood();
    inline void setAction(string s);
    inline string getAction();
    inline void setId(int x);
    inline int getId();
    void cardDescription();
    friend ostream &operator<<(ostream &output, Card &card);
    //virtual void takeActions(Player *pl, Graph* map) = 0;
    virtual void takeActions(Player *pl, Graph *map, vector<Player *> pls) = 0;
    virtual void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls) = 0;
};

class Card0 : public Card
{
public:
    Card0();
    ~Card0();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card1 : public Card
{
public:
    Card1();
    ~Card1();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card2 : public Card
{
public:
    Card2();
    ~Card2();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card3 : public Card
{
public:
    Card3();
    ~Card3();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card4 : public Card
{
public:
    Card4();
    ~Card4();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card5 : public Card
{
public:
    Card5();
    ~Card5();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card6 : public Card
{
public:
    Card6();
    ~Card6();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card7 : public Card
{
public:
    Card7();
    ~Card7();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card8 : public Card
{
public:
    Card8();
    ~Card8();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card9 : public Card
{
public:
    Card9();
    ~Card9();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card10 : public Card
{
public:
    Card10();
    ~Card10();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card11 : public Card
{
public:
    Card11();
    ~Card11();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card12 : public Card
{
public:
    Card12();
    ~Card12();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card13 : public Card
{
public:
    Card13();
    ~Card13();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card14 : public Card
{
public:
    Card14();
    ~Card14();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card15 : public Card
{
public:
    Card15();
    ~Card15();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card16 : public Card
{
public:
    Card16();
    ~Card16();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card17 : public Card
{
public:
    Card17();
    ~Card17();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card18 : public Card
{
public:
    Card18();
    ~Card18();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card19 : public Card
{
public:
    Card19();
    ~Card19();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

class Card20 : public Card
{
public:
    Card20();
    ~Card20();
    void takeActions(Player *pl, Graph *map, vector<Player *> pls);
    void takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls);
};

//TODO PlayerHand
//Factory class will produce different typey of cards
class CardsFactory
{
private:
    CardsFactory();

public:
    static Card *CreateCard(int id);
};

class Deck
{
public:
    Deck();
    ~Deck();
    void generateTop();
    void printDeck();
    void draw();
    void printCardSpace();

    Card *exchange(int row, Player &pl);
    string exchange_new(int row, Player &pl);
    vector<string> exchange_new2(int row, Player &pl);

    vector<Card *> deck;
    vector<Card *> cardSpace;
};

#endif
