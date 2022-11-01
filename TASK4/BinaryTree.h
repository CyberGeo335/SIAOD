#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <iostream>
#include <string>
#include <stack>

using namespace std;

struct TreeElements
{
    char temp;
    TreeElements* LeftPart;
    TreeElements* RightPart;
};

void Menu();

string ExpressionToRPN(string Expression);

int GetPriority(char token);

string CleaningTrash(string GlobalTemp);

TreeElements* ParserRPN(string ExpressionRPN);

void PrintingBinaryTree(TreeElements* Tree, int var);


#endif //BINARYTREE_BINARYTREE_H
