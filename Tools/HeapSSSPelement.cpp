
#include "HeapSSSPelement.h"

int HeapSSSPelement::getCost() {
    return cost;
}

int HeapSSSPelement::getIndex() {
    return index;
}

void HeapSSSPelement::setCost(int costNode)
{
    this->cost = costNode;
}

HeapSSSPelement::HeapSSSPelement(int index, int cost) :index(index),cost(cost), prev(-1)
{}


int HeapSSSPelement::getPrev() {
    return prev;
}

void HeapSSSPelement::setPrev(int prev)
{
    this->prev = prev;
}