#include "Menu.h"
#include "../Tools/CostAndPrevElement.h"
#include "../Tools/HeapSSSP.h"
#include "../Graphs/AdjacencyMatrix.h"
#include "../Graphs/AdjacencyList.h"
#include "../Tools/FileClass.h"
#include "../Tools/Timer.h"
#include <iostream>
#include <fstream>

using namespace std;

void Menu::showMenu()
{
    int choose;
    do {
        cout << "1. MST - Minimalne drzewo rozpinajace\n";
        cout << "2. SSSP - Najkrotsza sciezka\n";
        cout << "3. Testy\n";
        cout << "0. Zakoncz program\n";
        cout << "Wybierz opcje: ";

        cin >> choose; //wybrana opcja

        switch (choose)
        {
            case 1:
                Menu::showMenuMst();
                break;
            case 2:
                Menu::showMenuSSSP();
                break;
            case 3:
                Menu::showMenuAutomatic();
                break;
            case 0:
                break;
            default:
                cout << endl << "Podano nieprawidlowa opcje!" << endl;
                break;
        }
    } while (choose);
}

void Menu::showMenuAutomatic() {
    AdjacencyMatrix* matrix = new AdjacencyMatrix();
    AdjacencyList* list = new AdjacencyList();
    Timer timer;
    double time= 0.0;
    fstream file;

    int chooseOption = 0;
    int dataCount;

    cout << "Podaj ilosc kategorii danych: ";
    cin >> dataCount;

    int* data = new int [dataCount];
    int density[4] = {25,50,75,99};

    for (int i = 0; i < dataCount; ++i) {
        cout << i+1 << ": ";
        cin >> data[i];
    }


    do
    {
        cout << "1. MST - Algorytm Prima\n";
        cout << "2. MST - Algorytm Kruskala\n";
        cout << "3. SSSP - Algorytm Dijkstry\n";
        cout << "4. SSSP - Algorytm Bellman-Ford\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1: //MST - PRIMA
            {
                file.open("../Files/Output/test_Prima_Matrix.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (Matrix): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete matrix;
                            matrix = new AdjacencyMatrix(data[i],density[j], true);
                            timer.run();
                            matrix->algorithmPrima();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();

                file.open("../Files/Output/test_Prima_List.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (List): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete list;
                            list = new AdjacencyList(data[i],density[j], true);
                            timer.run();
                            list->algorithmPrima();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();
            }
                break;
            case 2: //MST - KRUSKAL
            {
                file.open("../Files/Output/test_Kruskal_Matrix.txt",ios::out);
                //matrix(1)/list(0);ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (Matrix): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete matrix;
                            matrix = new AdjacencyMatrix(data[i],density[j], true);
                            timer.run();
                            matrix->algorithmKruskal();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();

                file.open("../Files/Output/test_Kruskal_List.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (List): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete list;
                            list = new AdjacencyList(data[i],density[j], true);
                            timer.run();
                            list->algorithmKruskal();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();
            }
                break;
            case 3://SSSP - Dijkstra
            {
                file.open("../Files/Output/test_Dijkstra_Matrix.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (Matrix): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete matrix;
                            matrix = new AdjacencyMatrix(data[i],density[j], false);
                            timer.run();
                            matrix->algorithmDijkstra();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();

                file.open("../Files/Output/test_Dijkstra_List.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (List): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete list;
                            list = new AdjacencyList(data[i],density[j], false);
                            timer.run();
                            list->algorithmDijkstra();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();
            }
                break;
            case 4://SSSP - Bellman - Ford
            {
                file.open("../Files/Output/test_Bellman_Matrix.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (Matrix): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete matrix;
                            matrix = new AdjacencyMatrix(data[i],density[j], false);
                            timer.run();
                            matrix->algorithmBellmanFord();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();

                file.open("../Files/Output/test_Bellman_List.txt",ios::out);
                //ilość wierzchołków;pomiar dla 25%;pomiar dla 50%;pomiar dla 75%;pomiar dla 99%
                for (int i = 0; i < dataCount; ++i) {
                    file << data[i] <<';';
                    for (int j = 0; j < 4; ++j) {
                        cout <<"TEST (List): " <<data[i] <<", "<<density[j]<<"%: ";
                        for (int k = 0; k < 100; ++k) {
                            delete list;
                            list = new AdjacencyList(data[i],density[j], false);
                            timer.run();
                            list->algorithmBellmanFord();
                            timer.stop();
                            time += timer.getTimeMs();
                        }
                        cout << "X\n";
                        file << time/100 <<';';
                        time = 0.0;
                    }
                    file << '\n';
                }
                file.close();
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);
}

void Menu::showMenuMst() {
    AdjacencyMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    Timer timer;
    int chooseOption = 0;

    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wyswietl graf\n";
        cout << "3. MST - Algorytm Prima\n";
        cout << "4. MST - Algorytm Kruskala\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    AdjacencyList* newList;
                    newMatrix = FileClass::matrixFromFile(filename, false);
                    newList = FileClass::listFromFile(filename, false);
                    if (newMatrix != nullptr)
                    {
                        delete matrix;
                        delete list;
                        matrix = newMatrix;
                        list = newList;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2:	//WYŚWIETL GRAF
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    matrix->printMatrix();
                    list->printList();
                }
                break;
            case 3: //MST - PRIMA
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    timer.run();
                    Edge **mTable = matrix->algorithmPrima();
                    timer.stop();
                    cout << "Czas (matrix):" << timer.getTimeMs() << " ms" << endl;

                    timer.run();
                    Edge **lTable = list->algorithmPrima();
                    timer.stop();
                    cout << "Czas (list):" << timer.getTimeMs() << " ms" << endl;

                    int matrixMST = 0;
                    int listMST = 0;

                    cout << "MST - PRIMA - MACIERZ SASIEDZTWA" << endl;
                    cout << "  Edge  Weight" << endl;
                    for (int i = 0; i < matrix->getNodesCount() - 1; ++i) {
                        cout << "  " << '(' << mTable[i]->getVStart() << ',' << mTable[i]->getVEnd() << ')';
                        cout << "  " << mTable[i]->getWeight() << endl;
                        matrixMST += mTable[i]->getWeight();
                    }
                    cout << "MST=" << matrixMST << endl << endl;

                    cout << "MST - PRIMA - LISTA SASIEDZTWA" << endl;
                    cout << "  Edge  Weight" << endl;
                    for (int i = 0; i < list->getNodesCount() - 1; ++i) {
                        cout << "  " << '(' << lTable[i]->getVStart() << ',' << lTable[i]->getVEnd() << ')';
                        cout << "  " << lTable[i]->getWeight() << endl;
                        listMST += lTable[i]->getWeight();
                    }
                    cout << "MST=" << listMST << endl << endl;

                    delete[] lTable;
                    delete[] mTable;
                }
            }
                break;
            case 4: //MST - KRUSKAL
            {
                if (matrix == nullptr) {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    timer.run();
                    Edge **mTable = matrix->algorithmKruskal();
                    timer.stop();
                    cout << "Czas (matrix):" << timer.getTimeMs() << " ms" << endl;

                    timer.run();
                    Edge **lTable = list->algorithmKruskal();
                    timer.stop();
                    cout << "Czas (list):" << timer.getTimeMs() << " ms" << endl;

                    int matrixMST = 0;
                    int listMST = 0;

                    cout << "MST - KRUSKAL - MACIERZ SASIEDZTWA" << endl;
                    cout << "  Edge  Weight" << endl;
                    for (int i = 0; i < matrix->getNodesCount() - 1; ++i) {
                        cout << "  " << '(' << mTable[i]->getVStart() << ',' << mTable[i]->getVEnd() << ')';
                        cout << "  " << mTable[i]->getWeight() << endl;
                        matrixMST += mTable[i]->getWeight();
                    }
                    cout << "MST=" << matrixMST << endl << endl;

                    cout << "MST - KRUSKAL - LISTA SASIEDZTWA" << endl;
                    cout << "  Edge  Weight" << endl;
                    for (int i = 0; i < list->getNodesCount() - 1; ++i) {
                        cout << "  " << '(' << lTable[i]->getVStart() << ',' << lTable[i]->getVEnd() << ')';
                        cout << "  " << lTable[i]->getWeight() << endl;
                        listMST += lTable[i]->getWeight();
                    }
                    cout << "MST=" << listMST << endl << endl;

                    delete[] mTable;
                    delete[] lTable;
                }
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);
    //usuń tablice po zakonczeniu
    delete matrix;
    delete list;
}

void Menu::showMenuSSSP() {
    AdjacencyMatrix* matrix = nullptr;
    AdjacencyList* list = nullptr;
    Timer timer;
    int chooseOption = 0;
    do
    {
        cout << "1. Wczytaj graf z pliku\n";
        cout << "2. Wyswietl graf\n";
        cout << "3. SSSH - Algorytm Dijkstry\n";
        cout << "4. SSSH - Algorytm Bellmana-Forda\n";
        cout << "0. Wroc\n";
        cout << "Wybierz opcje: ";
        cin >> chooseOption; //wybrana opcje

        switch (chooseOption)
        {
            case 1:
                cout << "Pobieranie grafu z pliku tekstowego. Podaj nazwe pliku: ";
                {
                    string filename;
                    cin >> filename;
                    AdjacencyMatrix* newMatrix;
                    AdjacencyList* newList;
                    newMatrix = FileClass::matrixFromFile(filename, true);
                    newList = FileClass::listFromFile(filename, true);
                    if (newMatrix != nullptr)
                    {
                        delete matrix;
                        delete list;
                        matrix = newMatrix;
                        list = newList;
                    }
                    else
                        cout<< "ERROR IN READ"<<endl;
                }
                break;
            case 2:	//WYŚWIETL GRAF
                if (matrix == nullptr)
                {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else
                {
                    matrix->printMatrix();
                    list->printList();
                }
                break;
            case 3: //SSSP - DIJKSTRA
            {
                if (matrix == nullptr)
                {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    timer.run();
                    HeapSSSP *heapM = matrix->algorithmDijkstra();
                    timer.stop();
                    cout << "Czas (matrix):" << timer.getTimeMs() << " ms" << endl;

                    timer.run();
                    HeapSSSP *heapL = list->algorithmDijkstra();
                    timer.stop();
                    cout << "Czas (list):" << timer.getTimeMs() << " ms" << endl;

                    ///WYNIKI
                    int prevHelp;
                    int countTable = 0;
                    int *prevTable = new int[heapM->getSize()];

                    if (matrix->isNegativeEdge())
                        cout << "UJEMNE KRAWEDZIE! MOZLIWE BLEDY!\n";
                    cout << "SSSP - DIJKSTRA - MACIERZ SASIEDZTWA" << endl;
                    cout << "START = " << heapM->getStartNode() << endl;
                    cout << "End   Dist   Path" << endl;
                    for (int i = 0; i < heapM->getSize(); ++i) {
                        printf("%3d |%4d  | ", i, heapM->getCostNode(i));

                        prevHelp = i;
                        while (prevHelp != -1)      //uzupełnianie całkowitej ścieżki
                        {
                            prevTable[countTable++] = prevHelp;
                            prevHelp = heapM->getNode(prevHelp)->getPrev();
                            if (countTable > matrix->getNodesCount()) {
                                break;
                            }
                        }

                        for (int j = countTable - 1; j >= 0; --j) {
                            printf("%-2d ", prevTable[j]);
                        }
                        cout << endl;
                        countTable = 0;
                    }

                    if (list->isNegativeEdge())
                        cout << "UJEMNE KRAWEDZIE! MOZLIWE BLEDY!\n";
                    cout << endl << "SSSP - DIJKSTRA - LISTA SASIEDZTWA" << endl;
                    cout << "START = " << heapL->getStartNode() << endl;
                    cout << "End   Dist   Path" << endl;
                    for (int i = 0; i < heapL->getSize(); ++i) {
                        printf("%3d |%4d  | ", i, heapL->getCostNode(i));

                        prevHelp = i;
                        while (prevHelp != -1)      //uzupełnianie całkowitej ścieżki
                        {
                            prevTable[countTable++] = prevHelp;
                            prevHelp = heapL->getNode(prevHelp)->getPrev();
                            if (countTable > matrix->getNodesCount()) {
                                break;
                            }
                        }

                        for (int j = countTable - 1; j >= 0; --j) {
                            printf("%-2d ", prevTable[j]);
                        }
                        cout << endl;
                        countTable = 0;
                    }

                    delete heapM;
                    delete heapL;
                }
            }
                break;
            case 4: //SSSP - BELLMAN-FORD
            {
                if (matrix == nullptr)
                {
                    cout << "NIE WCZYTANO GRAFU!\n";
                } else {
                    timer.run();
                    CostAndPrevElement **tablePathM = matrix->algorithmBellmanFord();
                    timer.stop();
                    cout << "Czas (matrix):" << timer.getTimeMs() << " ms" << endl;

                    timer.run();
                    CostAndPrevElement **tablePathL = list->algorithmBellmanFord();
                    timer.stop();
                    cout << "Czas (list):" << timer.getTimeMs() << " ms" << endl;

                    //Sprawdzanie czy istnieje cykl ujemny
                    bool change = false;
                    int countEdge = 0;
                    Edge **edges = new Edge *[matrix->getEdgeCount()];
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        for (int j = 0; j < matrix->getNodesCount(); ++j) {
                            if (matrix->getWsk()[i][j] != nullptr)
                                edges[countEdge++] = matrix->getWsk()[i][j];         //zbieranie krawędzi do tablicy
                        }
                    }
                    for (int j = 0; j < matrix->getEdgeCount(); ++j) {
                        Edge *edge = edges[j];

                        if (tablePathM[edge->getVEnd()]->getCost() > (edge->getWeight() +
                                                                      tablePathM[edge->getVStart()]->getCost()))     //relaksacja - sprawdzamy czy nowa ścieżka będzie lepsza od aktualnej dla danego wierzchołka
                        {
                            tablePathM[edge->getVEnd()]->setCost(edge->getWeight() +
                                                                 tablePathM[edge->getVStart()]->getCost());   //jeśli tak, to zmień koszta i poprzednika
                            tablePathM[edge->getVEnd()]->setPrev(edge->getVStart());
                            change = true;  //nastąpiła zmiana, więc zmień status
                        }
                    }
                    //

                    if (change) //jeśli nastąpiła zmiana, oznacza to, że mamy cykl ujemny, zatem wyniki są niepoprawne
                    {
                        cout << "\nWYSTAPIL CYKL UJEMNY!!!\n";
                    } else
                    {
                        int *prevTable = new int[matrix->getNodesCount()];

                        ///WYNIKI
                        int prevHelp;
                        int countTable = 0;

                        cout << "SSSP - BELLMAN-FORD - MACIERZ SASIEDZTWA" << endl;
                        cout << "START = " << matrix->getStartNode() << endl;
                        cout << "End   Dist   Path" << endl;
                        for (int i = 0; i < matrix->getNodesCount(); ++i) {
                            printf("%3d |%4d  | ", i, tablePathM[i]->getCost());

                            prevHelp = i;
                            while (prevHelp != -1)      //uzupełnianie całkowitej ścieżki
                            {
                                prevTable[countTable++] = prevHelp;
                                prevHelp = tablePathM[prevHelp]->getPrev();
                                if (countTable > matrix->getNodesCount()) {
                                    break;
                                }
                            }

                            for (int j = countTable - 1; j >= 0; --j) {
                                printf("%-2d ", prevTable[j]);
                            }
                            cout << endl;
                            countTable = 0;
                        }

                        cout << "SSSP - BELLMAN-FORD - LISTA SASIEDZTWA" << endl;
                        cout << "START = " << list->getStartNode() << endl;
                        cout << "End   Dist   Path" << endl;
                        for (int i = 0; i < list->getNodesCount(); ++i) {
                            printf("%3d |%4d  | ", i, tablePathL[i]->getCost());

                            prevHelp = i;
                            while (prevHelp != -1)      //uzupełnianie całkowitej ścieżki
                            {
                                prevTable[countTable++] = prevHelp;
                                prevHelp = tablePathL[prevHelp]->getPrev();
                                if (countTable > matrix->getNodesCount()) {
                                    break;
                                }
                            }

                            for (int j = countTable - 1; j >= 0; --j) {
                                printf("%-2d ", prevTable[j]);
                            }
                            cout << endl;
                            countTable = 0;
                        }

                    }
                    for (int i = 0; i < matrix->getNodesCount(); ++i) {
                        delete tablePathL[i];
                        delete tablePathM[i];
                    }
                    delete[] tablePathL;
                    delete[] tablePathM;
                }
            }
                break;
            case 0:
                system("cls");
                break;
            default:
                cout << endl << "Podano niepoprawna opcje!" << endl;
                break;
        }
        cout << endl << endl;
    } while (chooseOption);
    //usuń tablice po zakonczeniu
    delete matrix;
    delete list;
}


