#include "HeapSSSP.h"

#include <cmath>
#include <iostream>
using namespace std;

HeapSSSP::HeapSSSP() : wsk(nullptr), size(0), heapSize(0)
{}
HeapSSSP::HeapSSSP(int size, int startNode)
{
    wsk = new HeapSSSPelement *[size];
    positionNodes = new int [size];

    heapSize = size;
    this->size = size;

    HeapSSSPelement* help;
    for (int i = 0; i < size; ++i) {
        wsk[i] = new HeapSSSPelement(i,INT32_MAX);      //dodawanie nowych, wierzho³ków (domyœlnie koszt dojœcia to INT32_MAX
        positionNodes[i] = i;                                     //zapamiêtujemy pozycje wierzcho³ków w kopcu, aby móc póŸniej szybko siê do nich odwo³aæ podczas zmiany
    }
    wsk[startNode]->setCost(0); //ustawienie kosztu przejœcia startowego wierzcho³ka na 0
    this->startNode = startNode;


    //Przeniesienie pocz¹tkowego wierzcho³ka startowego na sam szczyt kopca
    help = wsk[0];
    wsk[0] = wsk[startNode];
    positionNodes[wsk[0]->getIndex()] = 0;

    wsk[startNode] = help;
    positionNodes[wsk[startNode]->getIndex()] = startNode;


}
HeapSSSP::~HeapSSSP() {
    for (int i = 0; i < size; ++i) {
        delete wsk[i];
    }
    delete[] wsk;
    delete[] positionNodes;
}

HeapSSSPelement* HeapSSSP::pop() {

    if (heapSize==0)
    {
        return nullptr;
    }
    else
    {
        HeapSSSPelement* elementPop = wsk[0];

        wsk[0] = wsk[--heapSize];         //ostatni element przenieœ na sam szczyt
        positionNodes[wsk[0]->getIndex()] = 0;

        wsk[heapSize] = elementPop;           //zapamiêtaj usuniêty element poza kopcem
        positionNodes[wsk[heapSize]->getIndex()] = heapSize;

        heapifyTop();                     //przywróæ w³asnoœæ

        return elementPop;
    }
}

void HeapSSSP::heapifyToUp(int indexChild) {
    int child = indexChild;
    int parent = (child - 1)/2;
    HeapSSSPelement* help;
    while (child > 0 && wsk[parent]->getCost() > wsk[child]->getCost())
    {
        help = wsk[parent];
        wsk[parent] = wsk[child];
        positionNodes[wsk[parent]->getIndex()] = parent;

        wsk[child] = help;
        positionNodes[wsk[child]->getIndex()] = child;

        child = parent;
        parent = (child - 1)/2;
    }
}

void HeapSSSP::heapifyTop() {
    int leftChild = 1;
    int rightChild = 2;
    int min = 0;
    int parent = 0;
    HeapSSSPelement* help;

    do {
        min = parent;
        if (leftChild < heapSize && wsk[leftChild]->getCost() < wsk[min]->getCost())      //sprawdz czy lewe dziecko jest mniejsze od rodzica
        {
            min = leftChild;
        }

        if (rightChild < heapSize && wsk[rightChild]->getCost() < wsk[min]->getCost())    //sprawdz czy prawe dziecko jest mniejsze od min
        {
            min = rightChild;
        }

        if (min != parent)
        {
            help = wsk[parent];
            wsk[parent] = wsk[min];
            positionNodes[wsk[parent]->getIndex()] = parent;

            wsk[min] = help;
            positionNodes[wsk[min]->getIndex()] = min;

            parent = min;
            leftChild = (2*parent) + 1;
            rightChild = (2*parent) + 2;
        } else              //jeœli nie wykryto zmiany, zakoñcz
            break;

    } while (true);
}

void HeapSSSP::changeCost(int indexNode,int prevNode, int cost)
{
    wsk[positionNodes[indexNode]]->setCost(cost);       //zmieniamy koszt przejœcia dla podanego wierzcho³ka
    wsk[positionNodes[indexNode]]->setPrev(prevNode);   //zmieniamy poprzednika

    heapifyToUp(positionNodes[indexNode]);     //przywracamy w³aœnoœæ kopca w górê (w górê poniewa¿ zmiana zawsze nastêpuje jeœli wartoœæ jest mniejsza)
}

int HeapSSSP::getCostNode(int indexNode)
{
    return wsk[positionNodes[indexNode]]->getCost();
}

void HeapSSSP::print() {
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

bool HeapSSSP::isEmpty() {
    return heapSize <= 0;
}

int HeapSSSP::getStartNode() {
    return startNode;
}

HeapSSSPelement* HeapSSSP::getNode(int node) {
    return wsk[positionNodes[node]];
}

int HeapSSSP::getSize() {
    return size;
}
