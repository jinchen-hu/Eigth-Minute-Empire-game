#ifndef CARDSFACTORY_CPP
#define CARDSFACTORY_CPP
#include <iostream>
#include <ctime>
#include <algorithm>
#include <chrono>
#include <random>
#include "CardsFactory.h"
#include "Player.cpp"
#include "PlayerStrategies.cpp"
using namespace std;

//implementation of Card class
//done Card
Card::~Card()
{
    delete good;
    good = NULL;
    delete action;
    action = NULL;
    delete id;
    id = NULL;
}

inline void Card::setGood(string s)
{
    good = new string(s);
}

inline string Card::getGood()
{
    return *good;
}

inline void Card::setAction(string s)
{
    action = new string(s);
}

inline string Card::getAction()
{
    return *action;
}

inline void Card::setId(int x)
{
    id = new int(x);
}

inline int Card::getId()
{
    return *id;
}

void Card::cardDescription()
{
    cout << "Action: " << getAction() << ", Good: " << getGood() << endl;
}

ostream &operator<<(ostream &output, Card &card)
{
    output << card.getId() << ". " << card.getAction() << " - " << card.getGood() << endl;
    return output;
}

//implemetation of different types of cards
//done Card0
Card0::Card0()
{
    id = new int(0);
    action = new string("Place New Army 1");
    good = new string("GOOD: Wild");
}

Card0::~Card0() {}

void Card0::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        pl->placeNewArmies(map);
    }
}
void Card0::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    pl->placeNewArmies(map);
}

//done Card1
Card1::Card1()
{
    id = new int(1);
    action = new string("Place New Army 2");
    good = new string("GOOD: Carrot");
}

Card1::~Card1() {}

void Card1::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->placeNewArmies(map);
        }
    }
}
void Card1::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->placeNewArmies(map);
    }
}

//done Card2
Card2::Card2()
{
    id = new int(2);
    action = new string("Place New Army 3");
    good = new string("GOOD: Carrot");
}

Card2::~Card2() {}

void Card2::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 3; ++i)
        {
            pl->placeNewArmies(map);
        }
    }
}
void Card2::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 3; ++i)
    {
        pl->placeNewArmies(map);
    }
}

//done Card3
Card3::Card3()
{
    id = new int(3);
    action = new string("Place New Army 4");
    good = new string("GOOD: Carrot");
}

Card3::~Card3() {}

void Card3::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 4; ++i)
        {
            pl->placeNewArmies(map);
        }
    }
}

void Card3::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 4; ++i)
    {
        pl->placeNewArmies(map);
    }
}

//done Card4
Card4::Card4()
{
    id = new int(4);
    action = new string("Move Over Land 2");
    good = new string("GOOD: Carrot");
}

Card4::~Card4() {}

void Card4::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLand(map);
        }
    }
}
void Card4::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->moveOverLand(map);
    }
}

//done Card5
Card5::Card5()
{
    id = new int(5);
    action = new string("Move Over Land 3");
    good = new string("GOOD: Carrot");
}

Card5::~Card5() {}

void Card5::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 3; ++i)
        {
            pl->moveOverLand(map);
        }
    }
}

void Card5::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 3; ++i)
    {
        pl->moveOverLand(map);
    }
}

//TODO Card6
Card6::Card6()
{
    id = new int(6);
    action = new string("Move Over Land 4");
    good = new string("GOOD: Anvil");
}

Card6::~Card6() {}

void Card6::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 4; ++i)
        {
            pl->moveOverLand(map);
        }
    }
}

void Card6::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 4; ++i)
    {
        pl->moveOverLand(map);
    }
}

//done Card7
Card7::Card7()
{
    id = new int(7);
    action = new string("Move Over Land/Water 1");
    good = new string("GOOD: Anvil");
}

Card7::~Card7() {}

void Card7::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        pl->moveOverLandAndWater(map);
    }
}

void Card7::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    pl->moveOverLandAndWater(map);
}

//done Card8
Card8::Card8()
{
    id = new int(8);
    action = new string("Move Over Land/Water 2");
    good = new string("GOOD: Anvil");
}

Card8::~Card8() {}

void Card8::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
}

void Card8::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->moveOverLandAndWater(map);
    }
}

//done Card9
Card9::Card9()
{
    id = new int(9);
    action = new string("Move Over Land/Water 3");
    good = new string("GOOD: Anvil");
}

Card9::~Card9() {}

void Card9::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 3; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
}
void Card9::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 3; ++i)
    {
        pl->moveOverLandAndWater(map);
    }
}

//done Card10
Card10::Card10()
{
    id = new int(10);
    action = new string("Move Over Land/Water 4");
    good = new string("GOOD: Anvil");
}

Card10::~Card10() {}

void Card10::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 4; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
}
void Card10::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    for (int i = 0; i < 4; ++i)
    {
        pl->moveOverLandAndWater(map);
    }
}

//done Card11
Card11::Card11()
{
    id = new int(11);
    action = new string("Build A City");
    good = new string("GOOD: Crystal");
}

Card11::~Card11() {}

void Card11::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        pl->buildCity(map);
    }
}

void Card11::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    pl->buildCity(map);
}

//done Card12
Card12::Card12()
{
    id = new int(12);
    action = new string("Destroy An Army");
    good = new string("GOOD: Crystal");
}

Card12::~Card12() {}

void Card12::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        pl->destroyArmy(map, pls);
    }
}
void Card12::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    pl->destroyArmy(map, pls);
}

//done Card13
Card13::Card13()
{
    id = new int(13);
    action = new string("Move Over Land/Water 2 OR Destroy An Army");
    good = new string("GOOD: Crystal");
}

Card13::~Card13() {}

void Card13::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        cout << "1. Move Over Land/Water 2" << endl;
        cout << "2. Destroy An Army" << endl;
        int choice;
        do
        {
            cout << "Please enter your choice: ";
            cin >> choice;
        } while (choice != 1 && choice != 2);
        cout << endl;
        if (choice == 1)
        {
            cout << "Player [" << pl->getPlayerName() << "] chose: Move Over Land/Water 2" << endl;
            for (int i = 0; i < 2; ++i)
            {
                pl->moveOverLandAndWater(map);
            }
        }
        else if (choice == 2)
        {
            cout << "Player [" << pl->getPlayerName() << "] chose: Destroy an Army" << endl;
            pl->destroyArmy(map, pls);
        }
    }
}
void Card13::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    cout << "1. Move Over Land/Water 2" << endl;
    cout << "2. Destroy An Army" << endl;
    int choice;
    do
    {
        cout << "Please enter your choice: ";
        choice = rand() % 2;
    } while (choice != 1 && choice != 2);
    cout << endl;
    if (choice == 1)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Move Over Land/Water 2" << endl;
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
    else if (choice == 2)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Destroy an Army" << endl;
        pl->destroyArmy(map, pls);
    }
}

//done Card14
Card14::Card14()
{
    id = new int(14);
    action = new string("Move Over Land/Water 3 OR Destroy An Army");
    good = new string("GOOD: Crystal");
}

Card14::~Card14() {}

void Card14::takeActions(Player *pl, Graph* map, vector<Player*> pls){
    cout <<"Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if(!pl->ignore()){
        cout << "1. Move Over Land/Water 3" <<endl;
        cout << "2. Destroy An Army" << endl;
        int choice;

        do{
            cout << "Please enter your choice: ";
            cin >> choice;
        }while (choice !=1 && choice !=2);

        cout << endl;
        if(choice == 1){
            cout <<"Player [" << pl->getPlayerName() << "] chose: Move Over Land/Water 3" << endl;
            for(int i = 0; i < 3; ++i){
                pl->moveOverLandAndWater(map);
            }
        }else if(choice == 2){
            cout <<"Player [" << pl->getPlayerName() << "] chose: Destroy an Army" << endl;
            pl->destroyArmy(map, pls);
        }
    }

}

void Card14::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    cout << "1. Move Over Land/Water 3" << endl;
    cout << "2. Destroy An Army" << endl;
    int choice;

    do
    {
        cout << "Please enter your choice: ";
        choice = rand() % 2;
    } while (choice != 1 && choice != 2);

    cout << endl;
    if (choice == 1)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Move Over Land/Water 3" << endl;
        for (int i = 0; i < 3; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
    else if (choice == 2)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Destroy an Army" << endl;
        pl->destroyArmy(map, pls);
    }
}

//done Card15
Card15::Card15()
{
    id = new int(15);
    action = new string("Place New Army 2 OR Move over Land 2");
    good = new string("GOOD: Crystal");
}

Card15::~Card15() {}

void Card15::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        cout << "1. Place New Army 2" << endl;
        cout << "2. Move over Land 2" << endl;
        int choice;

        do
        {
            cout << "Please enter your choice: ";
            cin >> choice;
        } while (choice != 1 && choice != 2);

        cout << endl;
        if (choice == 1)
        {
            cout << "Player [" << pl->getPlayerName() << "] chose: Place New Army 2" << endl;
            for (int i = 0; i < 2; ++i)
            {
                pl->placeNewArmies(map);
            }
        }
        else if (choice == 2)
        {
            cout << "Player [" << pl->getPlayerName() << "] chose: Move over Land 2" << endl;
            for (int i = 0; i < 2; ++i)
            {
                pl->moveOverLand(map);
            }
        }
    }
}
void Card15::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    cout << "1. Place New Army 2" << endl;
    cout << "2. Move over Land 2" << endl;
    int choice;

    do
    {
        cout << "Please enter your choice: ";
        choice = rand() % 2;
    } while (choice != 1 && choice != 2);

    cout << endl;
    if (choice == 1)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Place New Army 2" << endl;
        for (int i = 0; i < 2; ++i)
        {
            pl->placeNewArmies(map);
        }
    }
    else if (choice == 2)
    {
        cout << "Player [" << pl->getPlayerName() << "] chose: Move over Land 2" << endl;
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLand(map);
        }
    }
}

//done Card16
Card16::Card16()
{
    id = new int(16);
    action = new string("Place New Army 2 AND Move over Land/Water 3");
    good = new string("GOOD: Timber");
}

Card16::~Card16() {}

void Card16::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    if (!pl->ignore())
    {
        cout << "Player [" << pl->getPlayerName() << "]: Place New Army 2 " << endl;
        for (int i = 0; i < 2; ++i)
        {
            pl->placeNewArmies(map);
        }
        cout << "Player [" << pl->getPlayerName() << "]: Move over Land/Water 3" << endl;
        for (int i = 0; i < 3; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }
}
void Card16::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;

    cout << "Player [" << pl->getPlayerName() << "]: Place New Army 2 " << endl;
    for (int i = 0; i < 2; ++i)
    {
        pl->placeNewArmies(map);
    }
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land/Water 3" << endl;
    for (int i = 0; i < 3; ++i)
    {
        pl->moveOverLandAndWater(map);
    }
}

//done Card17
Card17::Card17()
{
    id = new int(17);
    action = new string("Move over Land 1 AND Destroy an Army");
    good = new string("GOOD: Timber");
}

Card17::~Card17() {}

void Card17::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land 1" << endl;
    if (!pl->ignore())
    {
        pl->placeNewArmies(map);
    }

    cout << "Player [" << pl->getPlayerName() << "]: Destroy an Army" << endl;
    if (!pl->ignore())
    {
        pl->destroyArmy(map, pls);
    }
}
void Card17::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land 1" << endl;

    pl->placeNewArmies(map);

    cout << "Player [" << pl->getPlayerName() << "]: Destroy an Army" << endl;

    pl->destroyArmy(map, pls);
}

//done Card18
Card18::Card18()
{
    id = new int(18);
    action = new string("Move over Land 2 AND Build a City");
    good = new string("GOOD: Timber");
}

Card18::~Card18() {}

void Card18::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land 2" << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLand(map);
        }
    }

    cout << "Player [" << pl->getPlayerName() << "]: Build a City" << endl;
    if (!pl->ignore())
    {
        pl->buildCity(map);
    }
}
void Card18::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land 2" << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->moveOverLand(map);
    }

    cout << "Player [" << pl->getPlayerName() << "]: Build a City" << endl;

    pl->buildCity(map);
}
//done Card19
Card19::Card19()
{
    id = new int(19);
    action = new string("Place New Army 2 AND Build a City");
    good = new string("GOOD: Timber");
}

Card19::~Card19() {}

void Card19::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Place New Army 2" << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->placeNewArmies(map);
        }
    }

    cout << "Player [" << pl->getPlayerName() << "]: Build a City" << endl;
    if (!pl->ignore())
    {
        pl->buildCity(map);
    }
}

void Card19::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Place New Army 2" << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->placeNewArmies(map);
    }

    cout << "Player [" << pl->getPlayerName() << "]: Build a City" << endl;

    pl->buildCity(map);
}

//done Card20
Card20::Card20()
{
    id = new int(20);
    action = new string("Move over Land/Water 2 AND Destroy An Army");
    good = new string("GOOD: Timber");
}

Card20::~Card20() {}

void Card20::takeActions(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land/Water 2" << endl;
    if (!pl->ignore())
    {
        for (int i = 0; i < 2; ++i)
        {
            pl->moveOverLandAndWater(map);
        }
    }

    cout << "Player [" << pl->getPlayerName() << "]: Destroy an Army" << endl;
    if (!pl->ignore())
    {
        pl->destroyArmy(map, pls);
    }
}

void Card20::takeActionsComputer(Player *pl, Graph *map, vector<Player *> pls)
{
    cout << "Player [" << pl->getPlayerName() << "]: " << this->getAction() << endl;
    cout << "Player [" << pl->getPlayerName() << "]: Move over Land/Water 2" << endl;

    for (int i = 0; i < 2; ++i)
    {
        pl->moveOverLandAndWater(map);
    }

    cout << "Player [" << pl->getPlayerName() << "]: Destroy an Army" << endl;

    pl->destroyArmy(map, pls);
}

//implemetation of CardsFactory
CardsFactory::CardsFactory() {}

Card *CardsFactory::CreateCard(int id)
{
    switch (id)
    {
    case 0:
        return (new Card0());
        break;
    case 1:
        return (new Card1());
        break;
    case 2:
        return (new Card2());
        break;
    case 3:
        return (new Card3());
        break;
    case 4:
        return (new Card4());
        break;
    case 5:
        return (new Card5());
        break;
    case 6:
        return (new Card6());
        break;
    case 7:
        return (new Card7());
        break;
    case 8:
        return (new Card8());
        break;
    case 9:
        return (new Card9());
        break;
    case 10:
        return (new Card10());
        break;
    case 11:
        return (new Card11());
        break;
    case 12:
        return (new Card12());
        break;
    case 13:
        return (new Card13());
        break;
    case 14:
        return (new Card14());
        break;
    case 15:
        return (new Card15());
        break;
    case 16:
        return (new Card16());
        break;
    case 17:
        return (new Card17());
        break;
    case 18:
        return (new Card18());
        break;
    case 19:
        return (new Card19());
        break;
    case 20:
        return (new Card20());
        break;
    default:
        cout << "Invalid ID !!!" << endl;
        return NULL;
        break;
    }
}

Deck::Deck()
{
    //initial the deck
    //store 2 cards of each type
    for (int i = 0; i < 21; ++i)
    {
        deck.push_back((CardsFactory::CreateCard(i)));
        deck.push_back((CardsFactory::CreateCard(i)));
    }

    /*unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(deck.begin(), deck.end(), default_random_engine(seed));*/
    srand(unsigned(time(0)));
    random_shuffle(deck.begin(), deck.end());
    /*
    cout << "*********************************Print each card's description*********************************"<<endl;
    printDeck();
    generateTop();
    cout <<endl;cout <<endl;
    cout << "*********************************Print card space*********************************"<< endl;
    printCardSpace();*/
}

Deck::~Deck() {}

void Deck::printDeck()
{
    for (int i = 0; i < deck.size(); ++i)
    {
        cout << *(deck.at(i)) << endl;
    }
}

void Deck::generateTop()
{
    if (this->deck.size() == 42)
    {
        for (int i = 0; i < 6; i++)
        {
            draw();
        }
    }
    else
    {
        cout << "Something wroing when generating deck" << endl;
    }
}

void Deck::draw()
{
    if (deck.size() > 0)
    {
        //get the last card
        Card *last = deck.back();
        //delete the last card
        deck.pop_back();
        if (cardSpace.size() < 6)
        {
            cardSpace.push_back(last);
        }
        else
        {
            cout << "The card Space is full, the 6 spots are taken. Couldn't draw card from the deck." << endl;
        }
    }
    else
    {
        cout << "The deck is empty. Couldn't draw card from the deck." << endl;
    }
}

void Deck::printCardSpace()
{
    for (int i = 0; i < cardSpace.size(); ++i)
    {
        cout << (i + 1) << ". " << *(cardSpace.at(i)) << endl;
    }
}

Card *Deck::exchange(int row, Player &pl)
{

    switch (row)
    {
    case 0:
        cout << "You paid 0 coin for this card" << endl;
        pl.payCoins(0);
        break;
    case 1:
    case 2:
        cout << "You paid 1 coin for this card" << endl;
        pl.payCoins(1);
        break;
    case 3:
    case 4:
        cout << "You paid 2 coin for this card" << endl;
        pl.payCoins(2);
    case 5:
        cout << "You paid 3 coin for this card" << endl;
        pl.payCoins(3);
        break;
    default:
        cout << "Invalid" << endl;
        break;
    }
    if (row == 0)
    {
        pl.payCoins(0);
    }
    Card *drawn = cardSpace.at(row);
    pl.playerHand.push_back(drawn);
    cardSpace.erase(cardSpace.begin() + row);
    draw();
    return drawn;
}

string Deck::exchange_new(int row, Player &pl)
{
    //Card *draw = exchange(row, pl);
    return exchange(row, pl)->getAction();
}

vector<string> Deck::exchange_new2(int row, Player &pl)
{
    string action = exchange_new(row, pl);
    string position, pay;
    switch (row)
    {
    case 0:
        position = "first";
        pay = "zero";
        break;
    case 1:
        position = "second";
        pay = "one";
        break;
    case 2:
        position = "third";
        pay = "one";
        break;
    case 3:
        position = "forth";
        pay = "two";
        break;
    case 4:
        position = "fifth";
        pay = "two";
        break;
    case 5:
        position = "last";
        pay = "three";
        break;
    }
    vector<string> actionDescription;
    actionDescription.push_back(action);
    actionDescription.push_back(position);
    actionDescription.push_back(pay);
    return actionDescription;
}
#endif
