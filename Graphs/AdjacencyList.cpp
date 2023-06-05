#include "AdjacencyList.h"
#include "../Tools/Heap.h"
#include "../Tools/Set.h"
#include "../Tools/HeapSSSP.h"
#include "../Tools/CostAndPrevElement.h"
#include "../Tools/Array.h"
#include <iostream>
#include <iomanip>

using namespace std;

AdjacencyList::AdjacencyList():nodesCount(-1),edgeCount(-1),wsk(nullptr),startNode(-1),endNode(-1),negativeWeight(false)
{}

AdjacencyList::~AdjacencyList() {
    for (int i = 0; i < nodesCount; ++i) {
        ListElement* help = wsk[i];
        ListElement* toDelete;
        while(help)
        {
            toDelete = help;
            help = help->getNext();
            delete toDelete;
        }
    }
    delete[] wsk;
}

void AdjacencyList::addEdgeDirected(int VStart, int VEnd, int weight) {
    if (weight < 0)
        negativeWeight = true;
    wsk[VStart] = new ListElement(new Edge(VStart,VEnd,weight),wsk[VStart]);
}

void AdjacencyList::addEdgeNonDirected(int VStart, int VEnd, int weight) {
    if (weight < 0)
        negativeWeight = true;
    wsk[VStart] = new ListElement(new Edge(VStart,VEnd,weight),wsk[VStart]);
    wsk[VEnd] = new ListElement(new Edge(VEnd,VStart,weight),wsk[VEnd]);
}

void AdjacencyList::printList() {
    ListElement* help;
    cout << "LISTA SASIEDZTWA" << endl;
    for (int i = 0; i < nodesCount; ++i) {
        cout << setw(3) << i;
        help = wsk[i];
        while (help)
        {
            cout<<" -> "<<help->getEdge()->getVEnd()<<":"<<help->getEdge()->getWeight();
            help = help->getNext();
        }
        cout << endl;
    }
    cout << endl;
}

ListElement **AdjacencyList::getWsk() {
    return wsk;
}

int AdjacencyList::getNodesCount() {
    return nodesCount;
}

int AdjacencyList::getEdgeCount() {
    return edgeCount;
}

int AdjacencyList::getStartNode() {
    return startNode;
}

int AdjacencyList::getEndNode() {
    return endNode;
}

void AdjacencyList::fillListZero() {
    for (int i = 0; i < nodesCount; ++i) {
        wsk[i] = nullptr;
    }
}

AdjacencyList::AdjacencyList(int nodes, int edge, int start, int end) {
    nodesCount = nodes;
    edgeCount = edge;
    startNode = start;
    endNode = end;
    wsk = new ListElement *[nodesCount];
    negativeWeight = false;
    fillListZero();
}

Edge** AdjacencyList::algorithmKruskal() {
    ///OPIS DZIAŁANIA ALGORYTMU///
    //1.Tworzymy kopiec typu minimum, który służy nam za przechowywanie wszystkich krawędzi oraz ich posortowanie
    //2.Tworzymy tablice tableMST, która przechowuje nam krawędzie dodane do MST.
    //3.Tworzymy podzbiory rozłączne dla każdego wierzchołka
    //4.Wykonujemy V-1 wyborów krawędzi (tyle jest nam tylko potrzebne do zbudowania MST), za pomocą
    //pobierania kolejnej i kolejnej krawędzi z kopca. Jeśli 2 końce krawędzi znajdują się w 2 innych podzbiorach (mają inny korzeń)
    //to oznacza że nie mamy cyklu i dodajemy je do wyniku oraz łączymy ich pozbiory

    Heap* heap = new Heap(edgeCount * 2, true);      //kolejka priorytetowa jako kopiec
    Edge** tableMST = new Edge*[nodesCount-1];
    ListElement* helpElement;

    for (int i = 0; i < nodesCount; ++i) {
        helpElement = wsk[i];
        while (helpElement)                  //uzupełniaj dopóki masz kolejne elementy
        {
            heap->add(helpElement->getEdge());
            helpElement = helpElement->getNext();
        }
    }
    heap->buildHeap();  //budowanie kopca

    Set* helpSet = new Set(nodesCount); //utworzenie zbioru, który będzie przechowywał zbiory wierzchołków

    for (int i = 0; i < nodesCount; ++i) {
        helpSet->makeSet(i);                //dla każdego wierzchołka utwórz osobny zbiór
    }

    for (int i = 0; i < nodesCount - 1; ++i) {     //wykonywanie V-1 razy (MST posiada V-1 krawędzi)
        Edge* edgeHelp;

        do
        {
            edgeHelp = heap->pop();            //kolejna krawędź
        } while (helpSet->find(edgeHelp->getVStart())==helpSet->find(edgeHelp->getVEnd())); //sprawdzenie czy nie robi cyklu

        tableMST[i] = edgeHelp;                 //dodanie znalezionej krawędzi
        helpSet->unionSet(edgeHelp);      //złączenie 2 zbiorów wierzchołków
    }


    delete heap;
    delete helpSet;

    return tableMST;
}

Edge** AdjacencyList::algorithmPrima() {
    ///OPIS DZIAŁANIA ALGORYTMU///
    //1.Tworzymy tablice, która przechowuje czy dany wiezchołek został juz odwiedzony
    //2.Tworzymy kopiec typu minimum, który służy nam jako kolejka priorytetowa, do którego to będziemy dodawać kolejne krawędzie z wierzchołków
    //3.Tworzymy tablice tableMST, która przechowuje nam krawędzie dodane do MST.
    //4.Wierzchołek startowy ustawiamy domyślnie jako odwiedzony, reszta na nieodwiedzoną
    //5.Do kopca dodajemy wszystkie krawędzie, które są połączone z wierzchołkiem startowym
    //6.Wybieramy tyle krawędzi, aż nie skończy się kopiec lub uzyskamy V-1 krawędzi. Pobieramy z kopca krawędź o najmniejszej
    //wadze, następnie sprawdzamy czy końcowy wierzchołek jej krawędzi jest już odwiedzony.
    // Jeśli nie, to dodajemy ją do wyniku
    //oraz dodajemy do kopca wszystkie krawędzie, z którymi jest połączony końcowy wierzchołek. Potem wybieramy kolejną krawędź
    // Jeśli tak, to pobieramy kolejną krawędź

    bool* visitedNodes = new bool [nodesCount]; //tablica przechowująca dodane wierzchołki do drzewa
    Heap *queue = new Heap(edgeCount);      //kolejka priorytetowa jako kopiec
    Edge** tableMST = new Edge*[nodesCount-1];  //tablica przechowująca krawędzie MST
    ListElement* elementHelp;

    int nodeStart = 0;                          //wierzchołek startowy

    visitedNodes[nodeStart] = true;             //wierzchołek startowy jest odwiedzony
    for (int i = 1; i < nodesCount; ++i) {      //pozostałe wierzchołki jeszcze nie odwiedzone
        visitedNodes[i] = false;
    }

    elementHelp = wsk[nodeStart];
    while (elementHelp){             //wypełnij kolejke wszystkimi krawędziami z wierzchołka startowego
        queue->push(elementHelp->getEdge());
        elementHelp = elementHelp->getNext();
    }

    Edge* edgeFromQ;
    int nodeFromQ;
    int countEdgesMST = 0;
    int countMSTNode = 1;

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

            elementHelp = wsk[nodeFromQ];
            while (elementHelp){             //wypełnij kolejke wszystkimi krawędziami z nowego wierzhołka
                if (!visitedNodes[elementHelp->getEdge()->getVEnd()])
                    queue->push(elementHelp->getEdge());
                elementHelp = elementHelp->getNext();
            }
        }
    }

    delete queue;
    delete[] visitedNodes;

    return tableMST;
}

HeapSSSP* AdjacencyList::algorithmDijkstra() {
    ///OPIS DZIAŁANIA ALGORYTMU///
    //1.Tworzymy lekko zmodyfikowany kopiec typu minimum, który będzie przechowywał
    //nam wszystkie wierzchołki wraz z ich aktualnem kosztem dojścia i poprzednikiem w ścieżce. Podczas operacji pop()
    //nie usuwamy wierzchołka z tablicy (tylko z kopca), aby później móc go zmodyfikować, jeśli znajdzie się lepsza ścieżka dla niego
    //W kopcu zapisujemy też aktualne położenia danych wierzchołków w kopcu (po zmianie kosztu wierzchołka, zmienia się jego
    //pozycja w kopcu, lecz nie jego indeks).
    //Podczas inicjalizacji kopca dodajemy do niego obiekty HeapSSSPelement, które przechowują: koszt, indeks oraz indeks poprzednika
    //Na samym początku dla każdego elementu ustawiamy koszt dojścia na INT32_MAX, a poprzednika jako -1.
    //Tylko dla wierzchołka startowego zmieniamy koszt dojścia na 0 (będzie to pierwszy rozpatrywany wierzchołek)
    //2.Pobieramy wierzchołki do tego momentu, aż skończy skończy się kopiec.
    //Gdy pobierzemy wierzchołek z kopca, sprawdzamy każdego jego sąsiada.
    //Jeśli koszt dojścia do pobranego wierzchołka + waga krawędzi do rozpatrywanego sąsiada jest mniejsza, niż
    //aktualny koszt dojścia do rozpatrywanego sąsiada, to należy dokonać relaksacji.
    //Zamieniamy poprzednika rozpartywanego sąsiada na pobrany wierzchołek oraz zmieniamy koszt dojścia.
    //W przeciwnym razie, rozpatrujemy kolejnego sąsiada.
    //3. Po zakończeniu pętli, przeglądamy całą tablice kopca, i odczytujemy wyniki dla każdego wierzchołka

    HeapSSSP* heap = new HeapSSSP(nodesCount, startNode);  //kopiec jako kolejka priorytetowa, przechowująca wierzchołki wraz z kosztem dojścia (koszt dojścia jest kluczem)

    //Wykonujem dopóki w kopcu pozostały jeszcze nieużyte wierzchołki
    while (!heap->isEmpty())
    {
        HeapSSSPelement* elementFromHeap = heap->pop();         //zwróć wierzchołek z najmniejszym kosztem dojścia (ale zachowaj go w tablicy do możliwych późniejszych zmian)
        int currentNode = elementFromHeap->getIndex();          //wskaż który to wierzchołek

        ListElement* helpElement = wsk[currentNode];
        for (int i = 0; i < nodesCount; ++i) {
            while (helpElement)   //sprawdzamy każdego sąsiada wierzchołka
            {
                if (heap->getCostNode(helpElement->getEdge()->getVEnd()) > (helpElement->getEdge()->getWeight() + heap->getCostNode(currentNode)))     //relaksacja - sprawdzamy czy nowa ścieżka będzie lepsza od aktualnej dla danego wierzchołka
                {
                    heap->changeCost(helpElement->getEdge()->getVEnd(),currentNode,helpElement->getEdge()->getWeight() + heap->getCostNode(currentNode));  //jeśli tak, to zmień koszta i poprzednika
                }
                helpElement = helpElement->getNext();
            }
        }
    }

    return heap;
}

CostAndPrevElement** AdjacencyList::algorithmBellmanFord() {
    Edge** edges = new Edge* [edgeCount];
    CostAndPrevElement** tablePath = new CostAndPrevElement * [nodesCount];
    ListElement* elementHelp;
    bool change;

    int countEdge = 0;
    for (int i = 0; i < nodesCount; ++i) {
        tablePath[i] = new CostAndPrevElement();        //tworzenie elementów, które przechowują koszt ścieżki oraz poprzednika danego wierzchołka
        elementHelp = wsk[i];
        while (elementHelp)
        {
            edges[countEdge++] = elementHelp->getEdge();
            elementHelp = elementHelp->getNext();
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

AdjacencyList::AdjacencyList(int nodeAmount, int density, bool isMST) {
    nodesCount = nodeAmount;
    if (isMST)
        edgeCount = (nodeAmount - 1) + (((nodeAmount * (nodeAmount-1))/2 - (nodeAmount - 1)) * density)/100;        //obliczanie ilości wierzchołków przy podanej gęstości
    else
        edgeCount = (nodeAmount - 1) + ((nodeAmount * (nodeAmount-1) - (nodeAmount - 1)) * density)/100;        //obliczanie ilości wierzchołków przy podanej gęstości

    wsk = new ListElement *[nodesCount];

    fillListZero();                               //wypelnianie listy pustymi miejscami

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
        nodeTwoIndex = generator.getNumber(0,tableNodesToAdd->getSize()-1);     //wylosuj randowowy indeks
        nodeTwo = tableNodesToAdd->getByIndex(nodeTwoIndex);                              //znajdz wartosc wierzcholka przypisana do tego
        tableNodesToAdd->deleteIn(nodeTwoIndex);

        if (isMST)
            addEdgeNonDirected(nodeOne,nodeTwo,generator.getNumber(0,1000));
        else
            addEdgeDirected(nodeOne,nodeTwo,generator.getNumber(0,1000));

        nodeOne = nodeTwo;
        edgesAdded++;
    }

    Edge** tablePossibleEdges;
    if (isMST)
        tablePossibleEdges = new Edge * [nodesCount*(nodesCount-1)/2 - edgesAdded];
    else
        tablePossibleEdges = new Edge * [nodesCount*(nodesCount-1) - edgesAdded];

    int possibleEdges = 0;

    ListElement* helpElement;
    bool isNonDirectedExists = false;
    bool tableIsEdge[nodesCount];
    for (int i = 0; i < nodesCount; ++i) {
        tableIsEdge[i] = false;
    }

    for (int i = 0; i < nodesCount; ++i) {
        helpElement = wsk[i];
        while (helpElement)                  //przeglądaj dopóki istnieje kolejny element
        {
            tableIsEdge[helpElement->getEdge()->getVEnd()] = true;
            helpElement = helpElement->getNext();
        }
        for (int k = 0; k < nodesCount; ++k) {
            if (k==i)
                continue;
            if (!tableIsEdge[k])
            {
                if (isMST)
                {
                    for (int l = 0; l < possibleEdges; ++l) {
                        if (tablePossibleEdges[l]->getVStart() == k && tablePossibleEdges[l]->getVEnd() == i)   //jeśli istnieje już taka sama krawędź, tylko ma odwrotne wierzchołki, to nie dodawaj
                        {
                            isNonDirectedExists = true;
                            break;
                        }
                    }
                    if (!isNonDirectedExists)
                    {
                        tablePossibleEdges[possibleEdges++] = new Edge(i,k,-1);        //generowanie wszystkich możliwych krawędzi dostępnych
                    }
                    isNonDirectedExists = false;

                }
                else
                    tablePossibleEdges[possibleEdges++] = new Edge(i,k,-1);        //generowanie wszystkich możliwych krawędzi dostępnych
            }
        }
        for (int n = 0; n < nodesCount; ++n) {
            tableIsEdge[n] = false;
        }
    }

    while (edgesAdded < edgeCount)
    {
        int randomIndex = generator.getNumber(0,possibleEdges-1);
        Edge* edgeHelp = tablePossibleEdges[randomIndex];

        if (isMST)
            addEdgeNonDirected(edgeHelp->getVStart(),edgeHelp->getVEnd(),generator.getNumber(0,1000));
        else
            addEdgeDirected(edgeHelp->getVStart(),edgeHelp->getVEnd(),generator.getNumber(0,1000));


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

bool AdjacencyList::isNegativeEdge() {
    return negativeWeight;
}
