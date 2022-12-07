#pragma once
#include <iostream>
#include <string>
using namespace std;

class TreeNode
{
	string *keys;
	int *values;
	int t;
	TreeNode **C;
	int n;
	bool leaf;

public:
	TreeNode(int temp, bool bool_leaf);

	int findKey(string k);
	void insertNonFull(string k, int value);
	void splitChild(int i, TreeNode *y);
	void traverse();
	void deletion(string k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	string getPredecessor(int idx);
	string getSuccessor(int idx);
	void fill(int idx);
	void borrowFromPrev(int idx);
	void borrowFromNext(int idx);
	void merge(int idx);

	int search(string k);

	friend class BTree;
};

class BTree
{
	TreeNode *root;
	int t;

public:
	BTree(int temp)
	{
		root = NULL;
		t = temp;
	}

	void traverse()
	{
		if (root != NULL)
			root->traverse();
	}

	int search(string k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}

	void insert(string k, int value);
	void deletion(string k);
};