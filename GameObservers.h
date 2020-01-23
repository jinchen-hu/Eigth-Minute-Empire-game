// GameObservers.h
#pragma once
#include <string>
#include <list>

using namespace std;

// Observer Class
class Observer  
{
    public:
        Observer(); // constructor
        ~Observer(); // destructor
        virtual void Update2(string msg)=0;
        virtual void Update(string msg)=0; // Call to Update is done by an Observable object
};

// Observable Class
// will be our Players
class Observable
{
    protected:
        list <Observer *> *observers; // Observable has a list of observer objects

    public:
        Observable();
        ~Observable();
        virtual void Notify2(string msg);
        virtual void Notify(string msg); // Notify calls Update, from the Observer class
        virtual void Attach(Observer *o);
        virtual void Detach(Observer *o);
};