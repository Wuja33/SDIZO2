//
// Created by Dawid on 20.05.2023.
//

#include "ListElement.h"

ListElement *ListElement::getNext() {
    return next;
}

ListElement::ListElement(Edge* edge, ListElement *next): edge(edge),next(next)
{}

Edge* ListElement::getEdge() {
    return edge;
}
