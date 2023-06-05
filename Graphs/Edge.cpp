#include "Edge.h"

Edge::Edge(): vStart(-1), vEnd(-1), weight(-1)
{}
Edge::Edge(int getVStart, int getVEnd, int weight): vStart(getVStart), vEnd(getVEnd), weight(weight)
{}

int Edge::getVStart() {
    return vStart;
}

int Edge::getVEnd() {
    return vEnd;
}

int Edge::getWeight() {
    return weight;
}

