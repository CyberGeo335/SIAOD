#include "Huffman.h"

HuffmanAlgorithm::HuffmanAlgorithm(vector<Symbol> symbols, bool number, HuffmanAlgorithm* left, HuffmanAlgorithm* right)
{
    this->symbols = symbols;
    this->number = number;
    this->left = left;
    this->right = right;
}

HuffmanAlgorithm* HuffmanAlgorithm::GetMinNode(vector<HuffmanAlgorithm*>& nodes)
{
    float min = 1000.f;
    int minPos = 0;
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        float sumFrequency = getSumFrequency(nodes[i]->symbols);
        if (sumFrequency < min)
        {
            minPos = i;
            min = sumFrequency;
        }
    }
    HuffmanAlgorithm* result = nodes[minPos];
    nodes.erase(nodes.begin() + minPos);

    return result;
}

void HuffmanAlgorithm::AddingNode(vector<HuffmanAlgorithm*>& nodes, HuffmanAlgorithm* node)
{
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        if (nodes[i]->symbols[0].symbol == node->symbols[0].symbol)
            return;
    }
    nodes.push_back(node);
}

void HuffmanAlgorithm::SecondPrintTree(int levelNum)
{
    if (left == nullptr && right == nullptr)
        cout << string(levelNum * 4, ' ') << "(" << number << "|" << getString(symbols) << "|" << getSumFrequency(symbols) << ")" << endl;
    else
    {
        right->SecondPrintTree(levelNum + 1);
        if(levelNum != 0)
            cout << string(levelNum * 4, ' ') << "(" << number << "|" << getString(symbols) << "|" << getSumFrequency(symbols) << ")" << endl;
        else
            cout << string(levelNum * 4, ' ') << "(-|" << getString(symbols) << "|" << getSumFrequency(symbols) << ")" << endl;
        left->SecondPrintTree(levelNum + 1);
    }
}

string HuffmanAlgorithm::Encoding(string data)
{
    string result;

    vector<HuffmanAlgorithm*> nodes;
    for (unsigned int i = 0; i < data.size(); i++)
    {
        float frequency = getNumOfOccurrences(data, data[i]);
        AddingNode(nodes, new HuffmanAlgorithm(vector<Symbol> { Symbol { data[i], frequency } }, 0, nullptr, nullptr));
    }

    cout << "Таблица частотности:" << endl;
    for (unsigned int i = 0; i < nodes.size(); i++)
    {
        cout << getString(nodes[i]->symbols) << " : " << getSumFrequency(nodes[i]->symbols) << " " <<
             float(getSumFrequency(nodes[i]->symbols)) / data.size() << endl;
    }

    while (nodes.size() > 1)
    {
        HuffmanAlgorithm* minNodeLeft = GetMinNode(nodes);
        minNodeLeft->number = 0;
        HuffmanAlgorithm* minNodeRight = GetMinNode(nodes);
        minNodeRight->number = 1;

        HuffmanAlgorithm* node = new HuffmanAlgorithm(vector<Symbol> { Symbol { '-', getSumFrequency(minNodeLeft->symbols) + getSumFrequency(minNodeRight->symbols) }, Symbol{}}, 0, minNodeLeft, minNodeRight);
        nodes.push_back(node);
    }

    this->symbols = nodes[0]->symbols;
    this->number = nodes[0]->number;
    this->left = nodes[0]->left;
    this->right = nodes[0]->right;

    cout << "Префиксное дерево Хаффмана:" << endl;
    SecondPrintTree();

    int size = 0;
    string code;
    for (int i = 0; i < data.size(); i++)
    {
        code.clear();
        nodes[0]->FindCodeOfSymbol(data[i], code);
        code = code.substr(0, code.length() - 1);
        size += code.size();
        result += code + " ";
    }

    cout << "Коэффициент сжатия: " << float(data.size() * 8) / (size * 2) << endl;
    cout << "Средняя длина кода: " << (float)size / data.size() << endl;

    return result;
}

unsigned char HuffmanAlgorithm::GetBiteByBits(const string& bits)
{
    unsigned char result = 0;
    for (int i = bits.size() - 1; i >= 0; i--)
        result += (bits[i] - '0') * powf(2, (bits.size() - 1) - i);
    return result;
}

bool HuffmanAlgorithm::FindCodeOfSymbol(char symbol, string& result)
{
    if (symbols.size() == 1)
    {
        if (symbols[0].symbol == symbol)
        {
            result += to_string(number);
            return true;
        }
        else
            return false;
    }
    else
    {
        if (left->FindCodeOfSymbol(symbol, result))
        {
            result += to_string(number);
            return true;
        }
        else if (right->FindCodeOfSymbol(symbol, result))
        {
            result += to_string(number);
            return true;
        }
        return false;
    }
}

void HuffmanAlgorithm::EncodingFile(string fileInputName, string fileOutputName)
{
    //fileInputName += ".txt";
    //fileOutputName += ".dot";
    fileInputName;
    fileOutputName;

    ifstream fin(fileInputName);
    string input;
    string data;

    while (getline(fin, input))
        data += input;
    fin.close();

    string result;
    vector<HuffmanAlgorithm*> nodes;
    for (unsigned long int i = 0; i < data.size(); i++)
    {
        float frequency = getNumOfOccurrences(data, data[i]);
        AddingNode(nodes, new HuffmanAlgorithm( vector<Symbol> { Symbol { data[i], frequency } }, 0, nullptr, nullptr ));

    }

    while (nodes.size() > 1)
    {
        HuffmanAlgorithm* minNodeLeft = GetMinNode(nodes);
        minNodeLeft->number = 0;
        HuffmanAlgorithm* minNodeRight = GetMinNode(nodes);
        minNodeRight->number = 1;

        HuffmanAlgorithm* node = new HuffmanAlgorithm(vector<Symbol> { Symbol { '-', getSumFrequency(minNodeLeft->symbols) + getSumFrequency(minNodeRight->symbols) }, Symbol{}}, 0, minNodeLeft, minNodeRight );
        nodes.push_back(node);
    }

    this->symbols = nodes[0]->symbols;
    this->number = nodes[0]->number;
    this->left = nodes[0]->left;
    this->right = nodes[0]->right;

    string code;
    unsigned int currentBytePos = 0;
    string remainder;
    unsigned char currentByte = 0;

    for (unsigned int i = 0; i < data.size(); i++)
    {
        code.clear();
        nodes[0]->FindCodeOfSymbol(data[i], code);
        code = code.substr(0, code.length() - 1);

        if (currentBytePos >= 8)
        {
            while (remainder.size() > 8)
            {
                result += GetBiteByBits(remainder.substr(0, 8));
                remainder = remainder.substr(8);
            }
            result += currentByte;
            currentByte = 0;
            currentByte += GetBiteByBits(remainder);
            currentByte <<= remainder.size();
            currentBytePos = 0;
            currentBytePos += remainder.size();
            remainder.clear();
        }
        if (currentBytePos + code.size() < 8)
        {
            currentByte += GetBiteByBits(code);
            currentByte <<= code.size();
            currentBytePos += code.size();
        }
        else
        {
            string part = code.substr(0, 8 - currentBytePos);
            currentByte += GetBiteByBits(part);
            remainder = code.substr(8 - currentBytePos);
            currentBytePos += part.size();
        }
    }

    ofstream fout(fileOutputName, ios::binary);
    fout.write(result.c_str(), sizeof(char) * result.size());
    fout.close();
}
