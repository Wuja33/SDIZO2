#ifndef SDIZO2_SET_H
#define SDIZO2_SET_H


#include "SetNode.h"
#include "../Graphs/Edge.h"

class Set {
    SetNode* wsk;   //tablica, która będzie przechowywać zbiory
public:
    Set(int nodeCount);
    ~Set();

    int find(int value);        //znajdowanie korzenia
    void makeSet(int value);    //tworzenie zbioru dla wierzchołka
    void unionSet(Edge* edge);      //łączenie zbiorów za pomocą krawędzi
};


#endif //SDIZO2_SET_H
