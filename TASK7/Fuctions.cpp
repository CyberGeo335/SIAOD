#include "Functions.h"

int getNumOfOccurrences(string data, char symbol)
{
    int result = 0;

    for (long int i = 0; i < data.size(); i++)
    {
        if (data[i] == symbol)
            result++;
    }

    return result;
}

float getSumFrequency(vector<Symbol> symbols)
{
    float sum = 0.0f;
    for (int i = 0; i < symbols.size(); i++)
        sum += symbols[i].frequency;
    return sum;
}

string getString(vector<Symbol> symbols)
{
    string result;
    for (int i = 0; i < symbols.size(); i++)
        result += symbols[i].symbol;
    return result;
}
