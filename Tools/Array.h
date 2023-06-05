#pragma once

#include "../Tools/Timer.h"
#include "../Tools/Generator.h"

class Array
{
private:
    Generator generator;
	int* wsk;					//wskaŸnik tablicy
	unsigned size;					//wielkoœæ tablicy

public:
	Array();					//konstruktor domyœlny
	~Array();					//destruktor

    void addFirst(int);		    //dodaj element na pierwszej pozycji
    bool addIn(int, int);		//dodaj element w œrodku tablicy
    void addLast(int);			//dodaj element na koñcowej pozycji
	bool deleteFirst();			//usuñ element na pierwszej pozycji
	bool deleteIn(int);			//usuñ element w œrodku tablicy
	bool deleteLast();			//usuñ element na koñcowej pozycji
    int search(int);			//wyszukaj dany element w tablicy
    int getByIndex(int);		//wyszukaj dany element w tablicy
    void print();				//wyœwietlanie tablicy w konsoli
    void createTableTest(unsigned dataSize);				//wyœwietlanie tablicy w konsoli

    unsigned getSize();				//zwróæ wielkoœæ tablicy
	void setWsk(int*);				//zwróæ wskaŸnik
	void setSize(int);				//zwróæ wskaŸnik
};


