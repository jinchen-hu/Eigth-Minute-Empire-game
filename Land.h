#ifndef LAND_H
#define LAND_H

#include <string> 

using namespace std;

class Land 
{
    private:
        int ID;
        string name;

    public:
        Land();
        Land(int id, string name);
        int getID();
        void setID(int id);
        std::string getName();
        void setName(std::string country);
};

#endif