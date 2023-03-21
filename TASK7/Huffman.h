#ifndef HUFFMAN_H
#define HUFFMAN_H
#include "Functions.h"
#include <fstream>

class HuffmanAlgorithm
{
    private:
        vector<Symbol> symbols;
        bool number = 0;
        HuffmanAlgorithm* left = nullptr;
        HuffmanAlgorithm* right = nullptr;
        HuffmanAlgorithm* GetMinNode(vector<HuffmanAlgorithm*>& nodes);
        void AddingNode(vector<HuffmanAlgorithm*>& nodes, HuffmanAlgorithm* node);
        bool FindCodeOfSymbol(char symbol, string& result);
        unsigned char GetBiteByBits(const string& bits); // By DR. DRE XD
    public:
        HuffmanAlgorithm(vector<Symbol> symbols, bool number = 0, HuffmanAlgorithm* left = nullptr, HuffmanAlgorithm* right = nullptr);
        void EncodingFile(string fileInputName, string fileOutputName);
        string Encoding(string data);
        void SecondPrintTree(int levelNum = 0);
};

#endif
