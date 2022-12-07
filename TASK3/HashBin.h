#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

int i = 0;

struct Dict
{
    char eng[255];
    char rus[255];
};

struct TypeItembin // дерево
{
    char key[255]; // ключ
    int offset = 0; // значение, которое мы будем заполнять
    bool openOrClose = true; // открыта ли строка для записи
    bool deleteOrnot = false; // удалена ли строка или нет
};

struct HashTablebin // структура для элемов бинарной таблицы
{
    int L; // размер
    TypeItembin* T; // элемент в хэш-таблице
    int insertedCount;
    int deletedCount;
    void CreateHashTable(int k)
    {
        T = new TypeItembin[k];
        L = k;
        insertedCount = 0;
        deletedCount = 0;
    }
};

int InsertInHashTable(char* key, int offset, HashTablebin& t);

int search(HashTablebin& t, char* key);

int reHash(HashTablebin& old)
{
    int size = old.L;
    size = size + 10;
    HashTablebin new_hash;
    new_hash.CreateHashTable(size);
    for (int i = 0; i < size - 10; i++)
    {
        if (old.T[i].key != 0)
        {
            InsertInHashTable(old.T[i].key, old.T[i].offset, new_hash);
            int t = search(new_hash, old.T[i].key);
            new_hash.T[t].deleteOrnot = old.T[i].deleteOrnot;
            new_hash.T[t].openOrClose = old.T[i].openOrClose;
        }
    }
    old = new_hash;
    return 1;
}

int Hash(char* k, int L)
{
    char h1;
    if (k[0] % 2 == 0)
    {
        h1 = k[0] << 2 % 9;
    }
    else
    {
        h1 = 9 % k[0] << 2;
    }
    h1++;
    return h1 % L;
}

int InsertInHashTable(char* key, int offset, HashTablebin& t)
{
    if (t.insertedCount >= t.L * 0.75)
    {
        reHash(t);
    }
    int i = Hash(key, t.L);
    while (i < t.L && t.T[i].openOrClose == false)
    {
        if (i > t.L)
        {
            reHash(t);
        }
        i++;
    }
    if (i < t.L)
    {
        strcpy_s(t.T[i].key, key);
        t.T[i].offset = offset;
        t.T[i].openOrClose = false;
        t.insertedCount++;
        return 0;
    }
    else
    {
        return 1;
    }
}

void outTable(HashTablebin& t)
{
    cout << "номер" << '\t' << "ISBN" << '\t' << '\t' << "Номер записи" << '\t' << "свободен" << '\t' << "удален" << '\n';
    for (int i = 0; i < t.L; i++)
    {
        if (t.T[i].key == 0)
        {
            cout << i << '\t' << t.T[i].key << '\t' << '\t' << t.T[i].offset << '\t' << '\t' << t.T[i].openOrClose << '\t' << '\t' << t.T[i].deleteOrnot << '\n';
        }
        else
        {
            cout << i << '\t' << t.T[i].key << '\t' << t.T[i].offset << '\t' << '\t' << t.T[i].openOrClose << '\t' << '\t' << t.T[i].deleteOrnot << '\n';
        }
    }
}

int search(HashTablebin& t, char* key)
{
    int i = Hash(key, t.L);
    while (i < t.L && ((t.T[i].openOrClose == false && t.T[i].deleteOrnot == false) || (t.T[i].openOrClose == true && t.T[i].deleteOrnot == true)) && t.T[i].key != key)
    {
        i++;;
    }
    if (t.T[i].openOrClose == true && t.T[i].deleteOrnot == false)
    {
        return -1;
    }
    return t.T[i].offset;
}
void find(int i, ifstream& file)
{
    Dict dict;
    file.seekg(i * sizeof(Dict), ios::beg);
    file.read((char*)&dict, sizeof(dict));
    cout << dict.eng << ' ' << dict.rus << '\n';
}

int deleteFromHashTable(HashTablebin& t, char* key)
{
    int i = search(t, key);
    if (i == -1)
    {
        return 1;
    }
    else
    {
        strcpy_s(t.T[i].key, 0);
        t.T[i].offset = 0;
        t.T[i].deleteOrnot = true;
        t.T[i].openOrClose = true;
        t.deletedCount++;
        return 0;
    }
}

int ReadBin(HashTablebin& t, ifstream& bin_file)
{
    Dict dict;
    bool isGood = true;
    while (true)
    {
        bin_file.read((char*)&dict, sizeof(dict));
        if (!bin_file.eof())
        {
            if (InsertInHashTable(dict.eng, i, t) != 0)
            {
                isGood = false;
            }
            i++;
        }
        else
        {
            if (isGood)
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
}
//----------------------------------------
int line_counter(ifstream& file) // кол-во строк в файле
{
    string num_string = "";
    int counter = 1;
    while (!file.eof())
    {
        while (getline(file, num_string))
        {
            counter++;
        }
    }
    return counter;
}

void txt_to_bin(ifstream& txt_file, ofstream& bin_file)
{
    Dict dict;
    while (true)
    {
        txt_file >> dict.eng;
        if (!txt_file.eof())
        {
            txt_file >> dict.rus;
            bin_file.write((char*)&dict, sizeof(Dict));
        }
        else break;
    }

}
void AddToBin(ofstream& bin_file, Dict dict, HashTablebin& t)
{
    bin_file.seekp(0, ios::end);
    bin_file.write((char*)&dict, sizeof(Dict));
}

void bin_to_txt(ifstream& bin_file, ofstream& txt_file)
{

    Dict dict;
    while (true)
    {
        bin_file.read((char*)&dict, sizeof(dict));
        if (!bin_file.eof())
        {
            txt_file << dict.eng << " " << dict.rus << " ";
        }
        else
        {
            break;
        }
    }
}

void print_bin(ifstream& bin_file)
{
    Dict dict;
    while (true)
    {
        bin_file.read((char*)&dict, sizeof(dict));
        if (!bin_file.eof())
        {
            cout << dict.eng << ' ' << dict.rus << '\n';
        }
        else break;
    }
}

Dict get_struct(string filename, int position) // ищет структуру в файле
{
    Dict dict;
    ifstream bin_file(filename, ios::binary | ios::in);
    if (position == -1)
    {
        bin_file.seekg(-1 * (int)sizeof(dict), ios::end);
    }
    else
    {
        bin_file.seekg((position) * sizeof(dict));
    }
    bin_file.read((char*)&dict, sizeof(Dict));
    bin_file.close();
    return dict;
}

void remove_struct(string bin_name, char* key)
{

    Dict dict, replace{};
    replace = get_struct(bin_name, -1);
    ifstream bin_file(bin_name, ios::binary | ios::in);
    ofstream tmp("tmp_rem.txt");
    while (true)
    {
        bin_file.read((char*)&dict, sizeof(dict));

        if (!bin_file.eof())
        {
            if (dict.eng != key)
            {
                tmp << dict.eng << " " << dict.rus << "\n";
            }
            else
            {
                tmp << replace.eng << " " << replace.rus << "\n";
            }
        }
        else
        {
            break;
        }
    }
    tmp.close();
    bin_file.close();
    ifstream txt("tmp_rem.txt", ios::in);
    ofstream bin(bin_name, ios::binary);
    txt_to_bin(txt, bin);
    txt.close();
    bin.close();
}