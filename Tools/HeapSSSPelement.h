#ifndef SDIZO2_HEAPSSSPELEMENT_H
#define SDIZO2_HEAPSSSPELEMENT_H


class HeapSSSPelement {
    int index;      //wierzcho³ek
    int cost;       //koszt przejœcia do wierzcholka
    int prev;       //poprzednik wierzcho³ek w œcie¿ce
public:
    HeapSSSPelement(int index, int costNode);
    int getCost();
    int getIndex();
    int getPrev();
    void setCost(int cost);
    void setPrev(int prev);
};

#endif //SDIZO2_HEAPSSSPELEMENT_H
