#ifndef SDIZO2_HEAPSSSP_H
#define SDIZO2_HEAPSSSP_H


#include "HeapSSSPelement.h"

class HeapSSSP {
    HeapSSSPelement** wsk;
    int* positionNodes;
    int size;
    int heapSize;
    int startNode;

public:
    HeapSSSP();
    HeapSSSP(int size, int startNode);
    ~HeapSSSP();
    HeapSSSPelement* pop();
    void heapifyToUp(int indexChild);
    void heapifyTop();
    void changeCost(int indexNode, int prevNode, int cost);
    void print();

    int getCostNode(int indexNode);
    int getStartNode();
    int getSize();
    HeapSSSPelement* getNode(int node);
    bool isEmpty();
};


#endif //SDIZO2_HEAPSSSP_H
