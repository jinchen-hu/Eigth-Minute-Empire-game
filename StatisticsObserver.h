// The View
#pragma once

#include "GameObservers.h"
#include "Player.h"
#include <list>

class StatisticsObserver : public Observer
{
    protected:
        list <Player *> *observablePlayers; // Observer has a list of observabe objects

    public:
        void addObservablePlayer(Player *o);
        void removeObservablePlayer(Player *o);

        StatisticsObserver();
        ~StatisticsObserver();
        void Update2(string msg);
        void Update(string msg);
        void display(string msg);
        void displayStatistics();
};