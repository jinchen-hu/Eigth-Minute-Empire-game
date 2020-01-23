#ifndef MAP_H
#define MAP_H
#include <string>
#include <iostream>
#include <list>
#include "Country.h"
#include "MapAss.cpp"
using namespace std;

class Graph{
    

    public:
        int V;
        AdjList *arr;
        static Graph* getInstance(int V);
        //AdjListNode* newAdjListNode(Country data);
        void addEdge(Country src,Country dest);
        //void atk(Graph* graph, Country atk, Country dfn);
        //vector<Country> DFSUtil(Graph* graph, int v, bool visited[],vector<Country> * countriesInContinent, string continent);
        //vector<Country> DFS(Graph *graph, int v, string continent);
        void printGraph();
        //AdjListNode* newAdjListNode(Country data);
        //void printGraph2(Graph* graph, Country c[]);
    private:
        Graph();
        //Graph* createGraph(int V);
        Graph(int V);
        void setAList(int a);
        Graph(const Graph&);
        Graph &operator=(const Graph&);
        static Graph *map_instance;
        
};
#endif