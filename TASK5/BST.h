#pragma once
#include <iostream>
#include <string>
using namespace std;
class node
{
public:
	int value;
	char key[255];
	node *left, *right;
	node(string a, int b)
	{
		strcpy(key, a.c_str());
		value = b;
		left = nullptr;
		right = nullptr;
	}
	static bool exists(node * root, string a);
	static int search(node * root, string a);
	static node * insert(node * root, string a, int b);
	static class node *minValueNode(class node *node);
	static class node *deleteNode(class node *root, string key);
	static void printBT(const string& prefix, const node* node, bool isLeft, bool key);
};