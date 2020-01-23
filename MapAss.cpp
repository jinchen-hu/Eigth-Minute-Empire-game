#include "Country.h"

//struct for an adjacency list node
    struct AdjListNode{
        Country data;
        AdjListNode *next; 
    };

    //struct for an adjacency list
    struct AdjList{
        Country *country;
        AdjListNode *head;  //pointer to head node of list
    };

    AdjListNode* newAdjListNode(Country data){
        AdjListNode *nptr=new AdjListNode;
        nptr->data=data;
        nptr->next=NULL;
        return nptr;
    } 

    AdjList* setADJ(int a){
        return new AdjList[a];
    }