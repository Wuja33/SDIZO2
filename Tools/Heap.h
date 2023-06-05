#ifndef SDIZO_HEAP_H
#define SDIZO_HEAP_H
#include "../Graphs/Edge.h"

class Heap {
    Edge** wsk;
    int size;
    int heapSize;

public:
    Heap();
    Heap(int size);
    ~Heap();
    void push(Edge* edge);
    Edge* pop();
    void heapifyBottom();
    void heapifyTop();
    void print();
    bool isEmpty();

    int search(int i);
};


#endif //SDIZO_HEAP_H
