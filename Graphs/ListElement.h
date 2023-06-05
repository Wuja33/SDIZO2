//
// Created by Dawid on 20.05.2023.
//

#ifndef SDIZO2_LISTELEMENT_H
#define SDIZO2_LISTELEMENT_H


#include "../Graphs/Edge.h"

class ListElement {
    Edge* edge;
    ListElement* next;
public:
    ListElement(Edge* edge, ListElement* next);
    Edge* getEdge();
    ListElement* getNext();
};


#endif //SDIZO2_LISTELEMENT_H
