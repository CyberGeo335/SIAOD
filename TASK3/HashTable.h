#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>

using namespace std;

struct TypeItem
{
    int key = 0;
    int offset = 0;
    bool openOrClose = true;
    bool deleteOrnot = false;
};


struct HashTable
{
    int L; // размер
    TypeItem* T; // элемент в хэш-таблице
    int insertedCount;
    int deletedCount;
    void CreateHashTable(int k)
    {
        T = new TypeItem[k];
        L = k;
        insertedCount = 0;
        deletedCount = 0;
    }
};

int InsertInHashTable(int key, int offset, HashTable& t);

int search(HashTable& t, int key);

int reHash(HashTable& old)
{
    int size = old.L;
    size = size + 10;
    HashTable new_hash;
    new_hash.CreateHashTable(size);
    for (int i = 0; i < size - 10; i++)
    {
        if (old.T[i].key != 0)
        {
            InsertInHashTable(old.T[i].key, old.T[i].offset, new_hash);
            int j = search(new_hash, old.T[i].key);
            new_hash.T[j].deleteOrnot = old.T[i].deleteOrnot;
            new_hash.T[j].openOrClose = old.T[i].openOrClose;
        }
    }
    old = new_hash;
    return 1;
}

int Hash(int k, int L)
{
    int h1;
    if (k % 2 == 0)
    {
        h1 = k << 2 % 9;
    }
    else
    {
        h1 = 9 % k << 2;
    }
    h1++;
    return h1 % L;
}

int InsertInHashTable(int key, int offset, HashTable& t)
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
        t.T[i].key = key;
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

void outTable(HashTable& t)
{
    cout << "номер" << '\t' << "ключ" << '\t' << "значение" << '\t' << "свободен" << '\t' << "удален" << '\n';
    for (int i = 0; i < t.L; i++)
    {
        cout << i << '\t' << t.T[i].key << '\t' << t.T[i].offset << '\t' << '\t' << t.T[i].openOrClose << '\t' << '\t' << t.T[i].deleteOrnot << '\n';
    }
}

int search(HashTable& t, int key)
{
    int i = Hash(key, t.L);
    while (i < t.L && ((t.T[i].openOrClose == false && t.T[i].deleteOrnot == false) || (t.T[i].openOrClose == true && t.T[i].deleteOrnot == true)) && t.T[i].key != key)
    {
        i++;
        i = Hash(key, t.L);
    }
    if (t.T[i].openOrClose == true && t.T[i].deleteOrnot == false)
    {
        return -1;
    }
    return i;
}

int deleteFromHashTable(HashTable& t, int key)
{
    int i = search(t, key);
    if (i == -1)
    {
        return 1;
    }
    else
    {
        t.T[i].key = 0;
        t.T[i].offset = 0;
        t.T[i].deleteOrnot = true;
        t.T[i].openOrClose = true;
        t.deletedCount++;
        return 0;
    }
}