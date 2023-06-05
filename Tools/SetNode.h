#ifndef SDIZO2_SETNODE_H
#define SDIZO2_SETNODE_H


class SetNode {
    int parent;
    int rank;

public:
    int getParent();
    int getRank();
    void setParent(int parent);
    void setRank(int rank);
};


#endif //SDIZO2_SETNODE_H
