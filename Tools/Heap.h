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
    Heap(int size,bool build);
    ~Heap();
    void push(Edge* edge);
    void add(Edge* edge);
    Edge* pop();
    void buildHeap();
    void heapifyBottom();
    void heapifyTop();
    void heapify(int parent);
    void print();
    bool isEmpty();

    int search(int i);
};


#endif //SDIZO_HEAP_H
