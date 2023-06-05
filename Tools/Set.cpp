#include "Set.h"

Set::Set(int nodeCount) {
    wsk = new SetNode[nodeCount];   //utworzenie tablicy zbiorów
}

Set::~Set() {
    delete[] wsk;
}

int Set::find(int value) {                              //poszukiwanie korzenia
    if (wsk[value].getParent() != value)                //jeśli rodzic nie jest taki sam, jak podana wartość, to szukaj dalej
    {
        wsk[value].setParent(find(wsk[value].getParent())); //przypisanie znalezionego korzenia do rodziców (skrócenie poszukiwań korzenia w dalszych krokach)
        return wsk[value].getParent();
    }
    else
        return value;                                   //w przeciwnym wypadku jest to korzeń
}

void Set::makeSet(int value) {
    wsk[value].setParent(value);                        //na samym początku rodzic, to ten sam węzeł
    wsk[value].setRank(0);                              //ustawienie rank na 0, gdyż węzeł na ten moment jest sam
}

void Set::unionSet(Edge* edge) {
    int rootOne = find(edge->getVStart());   //szukam korzeni
    int rootTwo = find(edge->getVEnd());

    if (rootOne != rootTwo)     //sprawdzenie czy korzenie są takie same, jeśli tak -> oznacza to że wystąpił cykl
    {
        if (wsk[rootOne].getRank() > wsk[rootTwo].getRank())    //jeśli ranga wierzchołka 1 jest większa, to przyłącz 2 do 1
        {
            wsk[rootTwo].setParent(rootOne);
        }
        else
        {
            wsk[rootOne].setParent(rootTwo);                    //w przeciwnym razie dodaj 1 pod 2
            if (wsk[rootOne].getRank()==wsk[rootTwo].getRank()) //jeśli rangi są takie same, to zwiększ range rodzica
                wsk[rootTwo].setRank(wsk[rootTwo].getRank() + 1);
        }
    }
}
