
#include <iostream>
#include <string>
#include <regex>
#include <vector>
#include "MapLoader.cpp"
#include <algorithm>
#include <fstream>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
using namespace std;

int main(){

        cout << " Welcome to Eight Minute Empire Game" <<endl;
        cout << " Here are the maps you can choose" <<endl;
        // Read Maps Directory - Open directory
        struct dirent *entry;
        DIR *dir = opendir("/Users/chen/gitwork/Eight-Minute-Empire-game/MapsDirectory"); // hardcoded directory
        if (dir == NULL) 
        {
            // returns empty graph
            cout<< " Empty folder !!! "<< endl;
            return 0;
        }
        // regex with wordOrNumber.map
        int m=0;
        vector<string> dirMapNames; 
        while ( (entry = readdir(dir)) != NULL ) 
        {
            if( std::regex_match(entry->d_name, std::regex("(^([\\w]+)(\\.map)$)") ) )// if file ends with .map it's good
            {
                cout << (m+1) << ": " << entry->d_name << endl;
                dirMapNames.push_back(entry->d_name);
                m++;
            }
        }
        closedir(dir); // CLOSE DIRECTORY

        // user selects an indexed map, and we obtain the name of the map
        int mapIndex;
        cout << "Please choose the Map-ID you want to play with: ";
        cin >> mapIndex;
        mapIndex--;
        // display selected map
        cout << "You have chosen to load map: "<< dirMapNames.at(mapIndex) << endl;

        // load the selected indexed map
        cout << "Loading " << dirMapNames.at(mapIndex) << " ..." << endl;


        // (1)create graph (2)read map (3)Validate map (4)print map
        int graphSize = 0;
        
        // count nodes in file.map
        ifstream infile;
        string line;
        infile.open(dirMapNames.at(mapIndex)); // OPEN selected file name
        
        while (std::getline(infile, line))
        {
            // count nodes (one node per line)
            graphSize++;
        }
        infile.close(); // CLOSE

        cout << "Creating graph of size " << graphSize << "..." << endl;
        cout << "----------------------------------------------" <<endl;
        cout << endl;
        cout << endl;
        cout << "Graph *graph = Graph::getInstance();" << endl;
        cout << endl;
        // show the graph works ...
        Graph *graph = Graph::getInstance(graphSize);
        //cout << " dddddd"<< endl;
        bool valid = readMap(graph, dirMapNames.at(mapIndex));
        if(valid)
        {
            graph->printGraph();
        }
        else
        {
            printValidationError();
        }
        cout << endl;
        cout << endl;
        cout << "----------------------------------------------" <<endl;
        cout << endl;
        cout << endl;

        cout << "Graph *graph2 = Graph::getInstance();" << endl;
        //Graph *graph2 = new Graph();
        cout << " "<<endl;
        Graph *graph2 = Graph::getInstance(graphSize);
        //cout << " dddddd"<< endl;
        
        graph2->printGraph();
    
        cout << endl;
        cout << endl;
        cout << "----------------------------------------------" <<endl;
        cout << endl;
        cout << endl;
        
        cout << "Address of graph: " << graph <<endl;
        cout << "Address of graph2: " << graph2 <<endl;
        cout << "Do they share the same address: " << boolalpha << (graph == graph2) <<endl;
        return 0;
}
