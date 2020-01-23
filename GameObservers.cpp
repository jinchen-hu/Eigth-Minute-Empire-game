
// GameObservers.cpp
#include "GameObservers.h"
#include <list>

/*
* Observer object
*/ 
Observer::Observer(){};
Observer::~Observer(){};


/*
* Observable object
*/
Observable::Observable()
{
    observers = new list<Observer *>; // heap use
}
Observable::~Observable()
{
    //delete observers;
}
// attaching an observer to the Observable object, so that all observers will be Updated
void Observable::Attach(Observer *o)
{
    observers->push_back(o);
}
void Observable::Detach(Observer *o)
{
    observers->remove(o);
}
// Observable object notifies the observers
void Observable::Notify(string msg)
{
    list<Observer *>::iterator i = observers->begin();

    for ( ; i != observers->end(); i++)
    {
        (*i)->Update(msg); // CALLS Update() from Observer object
    }
}
void Observable::Notify2(string msg)
{
    list<Observer *>::iterator i = observers->begin();

    for ( ; i != observers->end(); i++)
    {
        (*i)->Update2(msg); // CALLS Update() from Observer object
    }
}

