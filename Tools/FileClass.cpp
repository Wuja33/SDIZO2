#include "FileClass.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

bool FileClass::file_read_line(ifstream &file, int tab[], int size)
{
    string s;
    getline(file, s);

    if(file.fail() || s.empty())
        return(false);

    istringstream in_ss(s);

    for(int i = 0; i < size; i++)
    {
        in_ss >> tab[i];
        if(in_ss.fail())
            return(false);
    }
    return(true);
}

AdjacencyMatrix* FileClass::matrixFromFile(string filename, bool directed)
{
    ifstream file;
    int tab[4];
    AdjacencyMatrix* matrix = nullptr;
    file.open(filename.c_str());

    if(file.is_open())
    {
        if(file_read_line(file, tab, 4))
        {
            matrix = new AdjacencyMatrix(tab[1],tab[0],tab[2],tab[3]);        //stworzenie nowej macierzy
            for(int i = 0; i < matrix->getEdgeCount(); i++)
                if(file_read_line(file, tab, 3))
                {
                    if (tab[0]>=0 && tab[0]<matrix->getNodesCount() && tab[1]>=0 && tab[1]<matrix->getNodesCount()) {
                        if (directed)
                            matrix->addEdgeDirected(
                                    new Edge(tab[0], tab[1], tab[2]));        //dodawanie nowych krawêdzi
                        else
                            matrix->addEdgeNonDirected(new Edge(tab[0], tab[1], tab[2]));
                    }
                    else
                    {
                        cout << "NIEPOPRAWNA WARTOSC WIERZCHOLKA" << endl;
                        delete matrix;
                        return nullptr;
                    }
                }
                else
                {
                    delete matrix;
                    cout << "File error - READ EDGE" << endl;
                    break;
                }
        }
        else
            cout << "File error - READ INFO" << endl;
        file.close();
    }
    else
        cout << "File error - OPEN" << endl;

    return matrix;
}

AdjacencyList *FileClass::listFromFile(string filename, bool directed) {
    ifstream file;
    int tab[4];
    AdjacencyList* list = nullptr;
    file.open(filename.c_str());

    if(file.is_open())
    {
        if(file_read_line(file, tab, 4))
        {
            list = new AdjacencyList(tab[1], tab[0], tab[2], tab[3]);        //stworzenie nowej listy
            for(int i = 0; i < list->getEdgeCount(); i++)
                if(file_read_line(file, tab, 3))
                {
                    if (tab[0]>=0 && tab[0] < list->getNodesCount() && tab[1] >= 0 && tab[1] < list->getNodesCount()) {
                        if (directed)
                            list->addEdgeDirected(tab[0], tab[1], tab[2]);        //dodawanie nowych krawêdzi
                        else
                            list->addEdgeNonDirected(tab[0], tab[1], tab[2]);
                    }
                    else
                    {
                        cout << "NIEPOPRAWNA WARTOSC WIERZCHOLKA" << endl;
                        delete list;
                        return nullptr;
                    }
                }
                else
                {
                    delete list;
                    cout << "File error - READ EDGE" << endl;
                    break;
                }
        }
        else
            cout << "File error - READ INFO" << endl;
        file.close();
    }
    else
        cout << "File error - OPEN" << endl;

    return list;
}
