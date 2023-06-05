//
// Created by Dawid on 27.05.2023.
//

#include <cstdint>
#include "CostAndPrevElement.h"

CostAndPrevElement::CostAndPrevElement():cost(INT32_MAX),prev(-1)
{}

void CostAndPrevElement::setCost(int newCost) {
    cost = newCost;
}

void CostAndPrevElement::setPrev(int newPrev) {
    prev = newPrev;
}

int CostAndPrevElement::getCost() {
    return cost;
}

int CostAndPrevElement::getPrev() {
    return prev;
}
