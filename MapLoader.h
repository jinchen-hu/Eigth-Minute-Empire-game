#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

class MapLoader{
    public:
    Graph* readMap(Graph *graph, string filename);
};

#endif