#include <cmath>
#include "Heap.h"
#include <iostream>
using namespace std;

Heap::Heap() : wsk(nullptr), size(0), heapSize(0)
{}
Heap::Heap(int size)
{
    wsk = new Edge*[size];
    for (int i = 0; i < size; ++i) {
        wsk[i] = nullptr;
    }
    heapSize = 0;
    this->size = size;
}
Heap::Heap(int size, bool buildAfter) {
    wsk = new Edge *[size];
    heapSize = 0;
    this->size = size;
}
Heap::~Heap() {
    delete[] wsk;
}
void Heap::add(Edge* edge) {
    wsk[heapSize++] = edge;
}
void Heap::buildHeap()
{
    for (int i = size/2 -1; i >= 0; --i) {
        heapify(i);
    }
}
void Heap::push(Edge* edge)
{
    wsk[heapSize++] = edge;             //wpisz nowa wartoœæ na ostatniej pozycji

    //przywrócenie w³asnoœci kopca po dodaniu
    heapifyBottom();
}

Edge* Heap::pop() {

    if (heapSize==0)
    {
        return nullptr;
    }
    else
    {
        Edge* edgePop = wsk[0];
        wsk[0] = wsk[--heapSize];         //ostatni element przenieœ na sam szczyt

        heapifyTop();                     //przywróæ w³asnoœæ

        return edgePop;
    }
}

void Heap::heapifyBottom() {
    int child = heapSize - 1;
    int parent = (child - 1)/2;
    Edge* help;
    while (child > 0 && wsk[parent]->getWeight() > wsk[child]->getWeight())
    {
        help = wsk[parent];
        wsk[parent] = wsk[child];
        wsk[child] = help;

        child = parent;
        parent = (child - 1)/2;
    }
}

void Heap::heapify(int parent) {
    int leftChild = (2*parent) + 1;
    int rightChild = (2*parent) + 2;

    int min = 0;
    Edge* help;

    do {
        min = parent;
        if (leftChild < heapSize && wsk[leftChild]->getWeight() < wsk[min]->getWeight())      //sprawdz czy lewe dziecko jest mniejsze od rodzica
        {
            min = leftChild;
        }

        if (rightChild < heapSize && wsk[rightChild]->getWeight() < wsk[min]->getWeight())    //sprawdz czy prawe dziecko jest mniejsze od min
        {
            min = rightChild;
        }

        if (min != parent)
        {
            help = wsk[parent];
            wsk[parent] = wsk[min];
            wsk[min] = help;

            parent = min;
            leftChild = (2*parent) + 1;
            rightChild = (2*parent) + 2;
        } else              //jeœli nie wykryto zmiany, zakoñcz
            break;

    } while (true);
}

void Heap::heapifyTop() {
    int leftChild = 1;
    int rightChild = 2;
    int min = 0;
    int parent = 0;
    Edge* help;

    do {
        min = parent;
        if (leftChild < heapSize && wsk[leftChild]->getWeight() < wsk[min]->getWeight())      //sprawdz czy lewe dziecko jest mniejsze od rodzica
        {
            min = leftChild;
        }

        if (rightChild < heapSize && wsk[rightChild]->getWeight() < wsk[min]->getWeight())    //sprawdz czy prawe dziecko jest mniejsze od min
        {
            min = rightChild;
        }

        if (min != parent)
        {
            help = wsk[parent];
            wsk[parent] = wsk[min];
            wsk[min] = help;

            parent = min;
            leftChild = (2*parent) + 1;
            rightChild = (2*parent) + 2;
        } else              //jeœli nie wykryto zmiany, zakoñcz
            break;

    } while (true);
}

void Heap::print() {
    if (size > 0 && wsk != nullptr)
    {
        bool outOfBound = false;
        int first = 0;
        int last = 1;

        // Calculate the maximum number of nodes at the current heap level
        int space = pow(2, floor(log2(this->size)) + 1) - 1;

        while (!outOfBound)
        {
            // Print space before each heap level
            cout << string(space / 2 * 3, ' ');

            // Print nodes on current heap level
            for (int i = first; i < last; i++)
            {
                if (i >= this->size)
                {
                    outOfBound = true;
                    break;
                }
                cout << '[' << wsk[i] << ']' << string(space * 3, ' ');
            }
            cout << "\n\n";

            // Change indexes or last and first node on each heap level
            first = last;
            last = 2 * last + 1;

            // Change size of space between nodes
            space = space / 2;
        }
        return;
    }
    cout << "Kopiec jest pusty" << std::endl;
}

bool Heap::isEmpty() {
    return heapSize <= 0;
}
