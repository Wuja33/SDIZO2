//
// Created by Dawid on 14.05.2023.
//

#include "AdjacencyMatrix.h"
#include "../Tools/Heap.h"
#include "../Tools/Set.h"
#include "../Tools/HeapSSSP.h"
#include "../Tools/Array.h"
#include <iostream>
#include <iomanip>

using namespace std;

AdjacencyMatrix::AdjacencyMatrix():nodesCount(-1),edgeCount(-1),wsk(nullptr),startNode(-1),endNode(-1)
{}
AdjacencyMatrix::~AdjacencyMatrix()
{
    for (int i = 0; i < nodesCount; ++i) {
        for (int j = 0; j < nodesCount; ++j) {
            delete wsk[i][j];
        }
    }
    delete[] wsk;
}

AdjacencyMatrix::AdjacencyMatrix(int nodes,int edge,int start, int end)
{
    nodesCount = nodes;
    edgeCount = edge;
    startNode = start;
    endNode = end;
    wsk = new Edge **[nodesCount];
    fillMatrixZero();
}

AdjacencyMatrix::AdjacencyMatrix(int nodeAmount, int density, bool isMST) {
    nodesCount = nodeAmount;
    if (isMST)
        edgeCount = (nodeAmount - 1) + (((nodeAmount * (nodeAmount-1))/2 - (nodeAmount - 1)) * density)/100;        //obliczanie ilości wierzchołków przy podanej gęstości
    else
        edgeCount = (nodeAmount - 1) + ((nodeAmount * (nodeAmount-1) - (nodeAmount - 1)) * density)/100;        //obliczanie ilości wierzchołków przy podanej gęstości

    wsk = new Edge **[nodesCount];

    fillMatrixZero();                               //wypelnianie macierzy pustymi miejscami

    Array* tableNodesToAdd = new Array();
    Generator generator;
    for (int i = 0; i < nodeAmount; ++i) {
        tableNodesToAdd->addLast(i);                //dodawnie wierzchołków do dynamicznej tablicy
    }
    int nodeOne = generator.getNumber(0,nodesCount - 1);    //wylosowanie 1 wierzchołka
    tableNodesToAdd->deleteIn(tableNodesToAdd->search(nodeOne));

    int nodeTwo, nodeTwoIndex;
    int edgesAdded = 0;
    while (tableNodesToAdd->getSize())              //wykonuj uzupełnianie
    {
        nodeTwoIndex = generator.getNumber(0,tableNodesToAdd->getSize()-1); //wylosuj randowowy indeks
        nodeTwo = tableNodesToAdd->getByIndex(nodeTwoIndex);                              //znajdz wartosc wierzcholka przypisana do tego
        tableNodesToAdd->deleteIn(nodeTwoIndex);

        if (isMST)
            addEdgeNonDirected(new Edge(nodeOne,nodeTwo,generator.getNumber(0,1000)));
        else
            addEdgeDirected(new Edge(nodeOne,nodeTwo,generator.getNumber(0,1000)));

        nodeOne = nodeTwo;
        edgesAdded++;
    }

    Edge** tablePossibleEdges;
    if (isMST)
        tablePossibleEdges = new Edge * [nodesCount*(nodesCount-1)/2 - edgesAdded];
    else
        tablePossibleEdges = new Edge * [nodesCount*(nodesCount-1) - edgesAdded];

    int possibleEdges = 0;
    int j;
    for (int i = 0; i < nodesCount; ++i) {
        if (isMST)
            j = 1+i;
        else
            j = 0;
        for (; j < nodesCount; ++j) {
            if (wsk[i][j] == nullptr && i!=j)
                tablePossibleEdges[possibleEdges++] = new Edge(i,j,-1);        //generowanie wszystkich możliwych krawędzi dostępnych
        }
    }

    while (edgesAdded < edgeCount)
    {
        int randomIndex = generator.getNumber(0,possibleEdges-1);
        Edge* edgeHelp = tablePossibleEdges[randomIndex];

        if (isMST)
            addEdgeNonDirected(new Edge(edgeHelp->getVStart(),edgeHelp->getVEnd(),generator.getNumber(0,1000)));
        else
            addEdgeDirected(new Edge(edgeHelp->getVStart(),edgeHelp->getVEnd(),generator.getNumber(0,1000)));


        delete tablePossibleEdges[randomIndex];
        Edge** tablePossibleEdgesNew = new Edge * [possibleEdges - 1];	    //utworzenie nowej tablicy o rozmiarze size - 1

        for (unsigned i = 0; i < randomIndex; i++)
        {
            tablePossibleEdgesNew[i] = tablePossibleEdges[i];				//kopiowanie elementów ze starej tablicy do nowej
        }

        for (unsigned i = randomIndex + 1; i < possibleEdges; i++)
        {
            tablePossibleEdgesNew[i - 1] = tablePossibleEdges[i];			//kopiowanie elementów ze starej tablicy do nowej
        }
        delete[] tablePossibleEdges;								        //usuwanie starej tablicy z pamięci

        possibleEdges--;										            //zmniejszenie wielkości tablicy o 1
        tablePossibleEdges = tablePossibleEdgesNew;							//przypisanie adresu nowej tablicy do zmiennej wsk

        edgesAdded++;
    }

    startNode = generator.getNumber(0,nodesCount-1);

    delete tableNodesToAdd;
    delete[] tablePossibleEdges;
}



void AdjacencyMatrix::fillMatrixZero() {    //wypełnianie macierzy domyślnie pustymi krawędziami oraz tworzenie macierzy
    for (int i = 0; i < nodesCount; ++i) {
        wsk[i] = new Edge*[nodesCount];
        for (int j = 0; j < nodesCount; ++j) {
            wsk[i][j] = nullptr;
        }
    }
}

Edge ***AdjacencyMatrix::getWsk() {
    return wsk;
}

int AdjacencyMatrix::getNodesCount() {
    return nodesCount;
}

int AdjacencyMatrix::getEdgeCount() {
    return edgeCount;
}

int AdjacencyMatrix::getEndNode() {
    return endNode;
}

int AdjacencyMatrix::getStartNode() {
    return startNode;
}

void AdjacencyMatrix::addEdgeDirected(Edge* edge) {
    wsk[edge->getVStart()][edge->getVEnd()] = edge;
}
void AdjacencyMatrix::addEdgeNonDirected(Edge* edge) {
    wsk[edge->getVStart()][edge->getVEnd()] = edge;
    wsk[edge->getVEnd()][edge->getVStart()] = new Edge(edge->getVEnd(),edge->getVStart(),edge->getWeight());
}
void AdjacencyMatrix::printMatrix() {
    cout << "MACIERZ SASIEDZTWA" << endl;
    cout << "    ";
    for(int i = 0; i < nodesCount; i++ )
    {
        cout << setw ( 3 ) << i << "|";
    }
    cout << endl;
    cout << setw(4*nodesCount+4) << setfill('-')<< '-' <<endl;
    cout<<setfill(' ');

    for(int i = 0; i < nodesCount; i++ )
    {
        cout << setw ( 3 ) << i << '|';
        for(int j = 0; j < nodesCount; j++ )
        {
            if (wsk[i][j] != nullptr)
                cout << setw (3) << wsk[i][j]->getWeight();
            else
                cout << setw (3) << '-';

            cout<<' ';
        }
        cout << endl;
    }
}

Edge** AdjacencyMatrix::algorithmKruskal() {
    Heap* queue = new Heap(edgeCount);      //kolejka priorytetowa jako kopiec
    Edge** tableMST = new Edge*[nodesCount-1];
    for (int i = 0; i < nodesCount; ++i) {
        for (int j=1+i; j < nodesCount; ++j) {  //dodawanie krawędzi tylko z jednej strony macierzy, (macierz jest symetryczna względem przekątnej)
            if (wsk[i][j] == nullptr)           //jeśli to null, to krawedź nie istnieje
                continue;
            else
                queue->push(wsk[i][j]);
        }
    }

    Set* helpSet = new Set(nodesCount); //utworzenie zbioru, który będzie przechowywał zbiory wierzchołków

    for (int i = 0; i < nodesCount; ++i) {
        helpSet->makeSet(i);                //dla każdego wierzchołka utwórz osobny zbiór
    }

    for (int i = 0; i < nodesCount - 1; ++i) {     //wykonywanie V-1 razy (MST posiada V-1 krawędzi)
        Edge* edgeHelp;

        do
        {
            edgeHelp = queue->pop();            //kolejna krawędź
        } while (helpSet->find(edgeHelp->getVStart())==helpSet->find(edgeHelp->getVEnd()));//sprawdzenie czy nie robi cyklu

        tableMST[i] = edgeHelp;                 //dodanie znalezionej krawędzi
        helpSet->unionSet(edgeHelp);      //złączenie 2 zbiorów wierzchołków
    }



    delete queue;
    delete helpSet;

    return tableMST;
}

Edge** AdjacencyMatrix::algorithmPrima() {
    bool* visitedNodes = new bool [nodesCount]; //tablica przechowująca dodane wierzchołki do drzewa
    Heap *queue = new Heap(edgeCount);      //kolejka priorytetowa jako kopiec
    Edge** tableMST = new Edge*[nodesCount-1];  //tablica przechowująca krawędzie MST

    int nodeStart = 0;                          //wierzchołek startowy
    int countMSTNode = 1;

    visitedNodes[nodeStart] = true;             //wierzchołek startowy jest odwiedzony
    for (int i = 1; i < nodesCount; ++i) {      //pozostałe wierzchołki jeszcze nie odwiedzone
        visitedNodes[i] = false;
    }

    for (int j = 0; j < nodesCount; ++j) {  //dodawanie krawędzi połączonych z wierzchołkiem startowym (dodajemy tylko krawędzie z jednej strony macierzy
        if (wsk[nodeStart][j] == nullptr)               //(maciersz symetryczna po przekątnej)  jeśli to null, to krawedź nie istnieje
            continue;
        else
            queue->push(wsk[nodeStart][j]);
    }

    Edge* edgeFromQ;
    int nodeFromQ;
    int countEdgesMST = 0;
    while (!queue->isEmpty())
    {
        edgeFromQ = queue->pop();                       //krawędź o najmniejszej wadze z kolejki
        nodeFromQ = edgeFromQ->getVEnd();
        if (!visitedNodes[nodeFromQ])                   //jeśli wierzchołek nie jest jeszcze odwiedzony
        {
            visitedNodes[nodeFromQ] = true;                     //ustawiam wierzhołek na odwiedzony
            tableMST[countEdgesMST++] = edgeFromQ;              //dodanie krawędzi do MST

            if (++countMSTNode == nodesCount)               //optymalizacja algorytmu --> jeśli przetworzono wszystkie wierzchołki, to można zakończyć
                break;

            for (int j = 0; j < nodesCount; ++j) {  //dodawanie krawędzi połączonych z wierzchołkiem (dodajemy tylko krawędzie z jednej strony macierzy
                if (wsk[nodeFromQ][j] == nullptr)               //(maciersz symetryczna po przekątnej)  jeśli to null, to krawedź nie istnieje
                    continue;
                else
                {
                    if (!visitedNodes[j])                       //dodajemy tylko krawędzie, które mają nieodwiedzone wierzchołki
                        queue->push(wsk[nodeFromQ][j]);       //dodaje krawędzie połączone z tym wierzchołkiem
                }
            }
        }
    }


    delete queue;
    delete[] visitedNodes;

    return tableMST;
}

HeapSSSP* AdjacencyMatrix::algorithmDijkstra() {
    HeapSSSP* heap = new HeapSSSP(nodesCount, startNode);  //kopiec jako kolejka priorytetowa, przechowująca wierzchołki wraz z kosztem dojścia (koszt dojścia jest kluczem)

    ///SZUKANIE NAJKRÓTSZEJ ŚCIEŻKI W GRAFIE. ROZPOCZYNAMY OD 0
    //Wykonujem dopóki w kopcu pozostały jeszcze nieużyte wierzchołki
    while (!heap->isEmpty())
    {
        HeapSSSPelement* elementFromHeap = heap->pop();
        int currentNode = elementFromHeap->getIndex();

        for (int i = 0; i < nodesCount; ++i) {
            if (wsk[currentNode][i]!= nullptr)   //sprawdzamy każdego sąsiada wierzchołka
            {
                if (heap->getCostNode(i) > (wsk[currentNode][i]->getWeight() + heap->getCostNode(currentNode)))     //relaksacja - sprawdzamy czy nowa ścieżka będzie lepsza od aktualnej dla danego wierzchołka
                {
                    heap->changeCost(i,currentNode,wsk[currentNode][i]->getWeight() + heap->getCostNode(currentNode));  //jeśli tak, to zmień koszta i poprzednika
                }
            }
        }
    }

    return heap;
}

CostAndPrevElement** AdjacencyMatrix::algorithmBellmanFord() {
    Edge** edges = new Edge* [edgeCount];
    CostAndPrevElement** tablePath = new CostAndPrevElement * [nodesCount];
    bool change;

    int countEdge = 0;
    for (int i = 0; i < nodesCount; ++i) {
        tablePath[i] = new CostAndPrevElement();        //tworzenie elementów, które przechowują koszt ścieżki oraz poprzednika danego wierzchołka
        for (int j = 0; j < nodesCount; ++j) {
            if (wsk[i][j] != nullptr)
                edges[countEdge++] = wsk[i][j];         //zbieranie krawędzi do tablicy
        }
    }

    tablePath[startNode]->setCost(0);           //ustawiamy koszt dojścia początkowego wierzchołka na 0

    ///SZUKANIE NAJKRÓTSZEJ ŚCIEŻKI W GRAFIE
    ///Wykonujem dopóki nie zajdzie żadna zmiana lub wykonamy v-1 iteracji

    for (int i = 0; i < nodesCount - 1; ++i) {
        change = false;
        for (int j = 0; j < edgeCount; ++j) {
            Edge* edge = edges[j];

            if (tablePath[edge->getVEnd()]->getCost() > (edge->getWeight() + tablePath[edge->getVStart()]->getCost()))     //relaksacja - sprawdzamy czy nowa ścieżka będzie lepsza od aktualnej dla danego wierzchołka
            {
                tablePath[edge->getVEnd()]->setCost(edge->getWeight() + tablePath[edge->getVStart()]->getCost());   //jeśli tak, to zmień koszta i poprzednika
                tablePath[edge->getVEnd()]->setPrev(edge->getVStart());
                change = true;  //nastąpiła zmiana, więc zmień status
            }
        }
        if (!change)
            break;          //jeśli nie było zmian, to zakończ algorytm
    }

    delete[] edges;
    return tablePath;
}


