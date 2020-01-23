#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "Map.cpp"

using namespace std;

Country* findCountryInGraph(Graph* graph, string countryName){
    string name;
    for(int i=0; i < graph->V; i++){
        name = graph->arr[i].country->getName();
        if(name == countryName){
            return graph->arr[i].country;
        }
    }
    Country *country = new Country;
    return country;
}

bool validate(string filename){
    ifstream input(filename);
    string element;
    while (getline(input,element,';'))
    {
        element.erase(std::remove(element.begin(), element.end(), '\n'), element.end());
        if(element.empty()){
            continue;
        }
        char id = element.at(0);
        if(!isdigit(id)){
            return false;
        }
        if(element.length()<3){
            return false;
        }
    }
    return true;
}

bool readMap(Graph *graph, string filename){
    ifstream input(filename);
    string countryString;
    string countryElement;

    if(!validate(filename)){
        return false;
    }

    while(getline(input,countryString,';')){
        countryString.erase(std::remove(countryString.begin(), countryString.end(), '\n'), countryString.end());
        if(countryString.empty()){
            continue;
        }
        Country *country = new Country;
        int elementIndex = 0;
        int countryIndex = 0;
        int id;

        stringstream stream(countryString);
        
        while(getline(stream,countryElement,','))
        {
             if(elementIndex == 0){
                 stringstream element(countryElement);
                 element >> id;
                country->setID(id);
            }
            if(elementIndex == 1){
                country->setName(countryElement);
            }
            if(elementIndex == 2){
                country->setContinent(countryElement);
            }
            
            elementIndex++;
        }
        graph ->arr[id-1].country = country;
        
        countryIndex++;
    }

    input.close();
    ifstream secondInputIteration(filename);
    while(getline(secondInputIteration,countryString,';')){
        countryString.erase(std::remove(countryString.begin(), countryString.end(), '\n'), countryString.end());
        if(countryString.empty()){
            continue;
        }
        Country country;
        int elementIndex = 0;
        int countryIndex = 0;
        int id;
         
        stringstream stream(countryString);
        Country *src;
        Country *dest;
        while(getline(stream,countryElement,',')){
            if(elementIndex == 0){
                 
                 stringstream element(countryElement);
                 element >> id;
                 src = graph->arr[id-1].country;
            }
             if(elementIndex > 2){
                dest = findCountryInGraph(graph,countryElement);
                if(dest->getName().empty()){
                    delete dest;
                    return false;
                }
                graph->addEdge(*src,*dest);
             }
            
            elementIndex++;
        }
        
        countryIndex++;
    }
    return true;
}

void printValidationError(){
    cout << "map is invalid" << endl;
}
