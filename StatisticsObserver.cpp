// StatisticsObserver.cpp
#include "StatisticsObserver.h"
#include "Player.cpp"
#include <iostream>

using namespace std;

StatisticsObserver::StatisticsObserver() // to initialize instances of child
{
    observablePlayers = new list <Player *>; 
}
StatisticsObserver::~StatisticsObserver()
{
    delete observablePlayers;
}

// adding an observable object to our Observer
void StatisticsObserver::addObservablePlayer(Player *o)
{
    observablePlayers->push_back(o);
}
// removing an observable object from our Observer
void StatisticsObserver::removeObservablePlayer(Player *o)
{
    observablePlayers->remove(o);
}

void StatisticsObserver::Update2(string msg){
    // display Info after Update()
    cout << "------------------------------New Update------------------------------" << endl;
    cout<<endl;
    cout << "         " << msg << "          " <<endl;
    cout<<endl;
    cout << "----------------------------------------------------------------------" << endl;
    
}

// UPDATE(), Called by 'Notify()' from Observed Player
void StatisticsObserver::Update(string msg)
{
    // Called by 'Notify()' from Observable
    display(msg);
}

void StatisticsObserver::display(string msg)
{
    // display Info after Update()
    cout << "------------------------------New Update------------------------------" << endl;
    cout << msg << endl;

    // display info of observable objects:
    if(this->observablePlayers->size() > 0)
    {
        list<Player *>::iterator i = observablePlayers->begin();

        for ( ; i != observablePlayers->end(); i++)
        {
            (*i)->print();
            (*i)->printCountries();
            cout<< (*i)->getPlayerName() << " has number of controlled countries: " <<  (*i)->getNumOfControlledCountries() << endl;

            cout << endl;
            cout << endl;
        }
    }

    // display Info after Update()
    cout << "----------------------------------------------------------------------" << endl;
}

