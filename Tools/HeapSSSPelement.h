#ifndef SDIZO2_HEAPSSSPELEMENT_H
#define SDIZO2_HEAPSSSPELEMENT_H


class HeapSSSPelement {
    int index;      //wierzcho�ek
    int cost;       //koszt przej�cia do wierzcholka
    int prev;       //poprzednik wierzcho�ek w �cie�ce
public:
    HeapSSSPelement(int index, int costNode);
    int getCost();
    int getIndex();
    int getPrev();
    void setCost(int cost);
    void setPrev(int prev);
};

#endif //SDIZO2_HEAPSSSPELEMENT_H
