#ifndef SDIZO2_ADJACENCYLIST_H
#define SDIZO2_ADJACENCYLIST_H
#include "./ListElement.h"
#include "Edge.h"
#include "../Tools/HeapSSSP.h"
#include "../Tools/CostAndPrevElement.h"

class AdjacencyList {
    ListElement** wsk;
    int nodesCount;
    int edgeCount;
    int startNode;
    int endNode;
    bool negativeWeight;
public:
    AdjacencyList();
    AdjacencyList(int nodes,int edge,int start, int end);
    AdjacencyList(int nodeAmount, int density, bool isMST);
    ~AdjacencyList();

    void fillListZero();
    void addEdgeDirected(int VStart, int VEnd, int weight);
    void addEdgeNonDirected(int VStart, int VEnd, int weight);
    void printList();

    Edge** algorithmKruskal();
    Edge** algorithmPrima();

    HeapSSSP* algorithmDijkstra();
    CostAndPrevElement** algorithmBellmanFord();

    ListElement** getWsk();
    int getNodesCount();
    int getEdgeCount();
    int getStartNode();
    int getEndNode();
    bool isNegativeEdge();
};


#endif //SDIZO2_ADJACENCYLIST_H
