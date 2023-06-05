#ifndef SDIZO2_COSTANDPREVELEMENT_H
#define SDIZO2_COSTANDPREVELEMENT_H


class CostAndPrevElement {
    int cost;       //koszt œcie¿ki
    int prev;       //poprzednik
public:
    CostAndPrevElement();
    void setCost(int newCost);
    void setPrev(int newPrev);
    int getCost();
    int getPrev();
};


#endif //SDIZO2_COSTANDPREVELEMENT_H
