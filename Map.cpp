#include<iostream>
#include<cstdlib>
//#include "Country.cpp"
#include "Map.h"

using namespace std;

Graph *Graph::map_instance = NULL;

Graph::Graph(){}

Graph::Graph(const Graph&){}

Graph&Graph::operator=(const Graph&){
    return *this;
}
//create a new node
Graph::Graph(int V){
    this->V=V;
    //create an array of adjacency list. size of array - V
    arr = setADJ(V);
    //initialize with NULL (e.g root=NULL)
    for(int i=0;i<V;i++){
        this->arr[i].head=NULL;
    }
}
void Graph::setAList(int a){
    this->arr = new AdjList[a];
}
Graph* Graph::getInstance(int V){
    if(!map_instance){
        map_instance = new Graph(V);
    }
    return map_instance;
}



//add an edge to an undirected Graph
void Graph::addEdge(Country src,Country dest){
    //Add an edge from src to dest. A new node added to the adjacency list of src
    //node added at beginning
    AdjListNode *nptr = newAdjListNode(dest);
    nptr->next = this->arr[src.getID()-1].head;
    this->arr[src.getID()-1].head=nptr;
    //connect from dest to src (since undirected)
    nptr = newAdjListNode(src);
    nptr->next=this->arr[dest.getID()-1].head;
    this->arr[dest.getID()-1].head=nptr;
}



void Graph::printGraph(){
    for(int i=0; i<this->V;i++){
        AdjListNode *root = this->arr[i].head;
        cout<<"Adjacency list of vertex "<< this->arr[i].country->getName()<<endl;
        //loop over each node in list
       while(root!=NULL){
           cout<< "-> " << root->data.getName();
           root=root->next;
       }
       cout << endl;
    }
}
