#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <string>
#include <vector>
#include "math.h"

using namespace std;

struct Symbol
{
    char symbol = 0;
    float frequency = 0.f;
};

float getSumFrequency(vector<Symbol> symbols);
int getNumOfOccurrences(string data, char symbol);
string getString(vector<Symbol> symbols);

#endif
