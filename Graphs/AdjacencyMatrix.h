#ifndef SDIZO2_ADJACENCYMATRIX_H
#define SDIZO2_ADJACENCYMATRIX_H
#include "Edge.h"
#include "../Tools/HeapSSSP.h"
#include "../Tools/CostAndPrevElement.h"

class AdjacencyMatrix {
    Edge*** wsk;
    int nodesCount;
    int edgeCount;
    int startNode;
    int endNode;

public:
    ~AdjacencyMatrix();
    AdjacencyMatrix();
    AdjacencyMatrix(int nodes,int edge,int start, int end);
    AdjacencyMatrix(int nodeAmount, int density, bool isMST);

    void fillMatrixZero();
    void addEdgeDirected(Edge* edge);
    void addEdgeNonDirected(Edge* edge);
    void printMatrix();

    Edge** algorithmKruskal();
    Edge** algorithmPrima();


    HeapSSSP* algorithmDijkstra();
    CostAndPrevElement** algorithmBellmanFord();

    Edge*** getWsk();
    int getNodesCount();
    int getEdgeCount();
    int getStartNode();
    int getEndNode();

};


#endif //SDIZO2_ADJACENCYMATRIX_H
