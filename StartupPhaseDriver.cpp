
#include <string>
#include <iostream>

#include "StartupPhase.cpp"

int main()
{
    //cout<< "main" << endl;
    StartupPhase startup = StartupPhase();
    
    startup.shuffleAndDrawCards();

    startup.playersPlacingOnMap();

    return 0;
}