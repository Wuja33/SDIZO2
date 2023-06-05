#ifndef SDIZO2_EDGE_H
#define SDIZO2_EDGE_H


class Edge {
    int vStart;         //wierzchołek 1
    int vEnd;         //wierzchołek 2
    int weight;     //waga krawędzi
public:
    Edge();
    Edge(int vStart, int vEnd, int weight);

    int getVStart();
    int getVEnd();
    int getWeight();
};


#endif //SDIZO2_EDGE_H
