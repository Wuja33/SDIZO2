#ifndef SDIZO_GENERATOR_H
#define SDIZO_GENERATOR_H
#include <random>
#include <iostream>
using namespace std;

class Generator {
    random_device rd;
    mt19937 gen;
    uniform_int_distribution<> dist;
public:
    Generator();
    int getNumber();
    int getNumber(int min, int max);
};


#endif //SDIZO_GENERATOR_H
