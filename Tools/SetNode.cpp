#include "SetNode.h"

int SetNode::getParent() {
    return parent;
}

int SetNode::getRank() {
    return rank;
}

void SetNode::setParent(int parent) {
    this->parent = parent;
}

void SetNode::setRank(int rank) {
    this->rank = rank;
}
