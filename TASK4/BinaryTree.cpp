#include "BinaryTree.h"

void Menu()
{
    cout << "========================== ПРАКТИЧЕСКАЯ РАБОТА № 4 ==========================" << endl;
    cout << "================================ ВАРИАНТ № 10 ===============================" << endl;
    cout <<"1) Создание дерева на основе математического выражения;" << endl;
    cout <<"2) Вывод дерева на основе пункта 1;" << endl;
    cout <<"3) Определить функцию упрощения дерева ? выражения," << endl;
    cout <<"заменяя в нем все поддеревья, соответствующие формулам:"<< endl;
    cout <<"(f+0),(0+f),(f-0),(f*1),(1*f) на поддеревья,"<<endl;
    cout <<"соответствующие формуле f. А поддеревья вида (f*0) и (0*f) заменить на вершину с 0;" << endl;
    cout <<"4) Завершение работы;"<<endl;
    cout << "=============================================================================" << endl;
}

TreeElements* CreateTreeElements(char temp)
{
    TreeElements* elem = new TreeElements;
    elem -> temp = temp;
    elem -> RightPart = nullptr;
    elem -> LeftPart = nullptr;
    return elem;
}

int GetPriority(char token)
{
    if (token == '*' || token == '/')
        return 3;
    else if (token == '+' || token == '-')
        return 2;
    else if (token == '(')
        return 1;
    else if (token == ')')
        return -1;
    else
        return 0;
}

string ExpressionToRPN(string Expression)
{
    string Current = "";

    stack <char> Stack;

    int Priority;

    for (int i = 0; i < Expression.length(); i++)
    {
        Priority = GetPriority(Expression[i]);

        if (Priority == 0)
        {
            Current += Expression[i];
        }

        else if (Priority == 1)
        {
            Stack.push(Expression[i]);
        }

        else if (Priority > 1)
        {
            Current += ' ';
            while (!Stack.empty())
            {
                if(GetPriority(Stack.top()) >= Priority )
                {
                    char temp1 = Stack.top();
                    Current += temp1;
                    Stack.pop();
                }
                else
                {
                    break;
                }
            }
            Stack.push(Expression[i]);
        }

        else if (Priority == -1)
        {
            Current += ' ';
            while(GetPriority(Stack.top()) != 1)
            {
                char temp2 = Stack.top();
                Current += temp2;
                Stack.pop();
            }
            Stack.pop();
        }


    }
    while (!Stack.empty())
    {
        char temp3 = Stack.top();
        Current += temp3;
        Stack.pop();
    }

    return Current;
}

TreeElements* ParserRPN(string ExpressionRPN)
{
    stack <TreeElements*> StackTree;

    TreeElements* te;

    for (int i = 0; i < ExpressionRPN.size(); i++)
    {
        if (isdigit(ExpressionRPN[i]))
        {
            te = CreateTreeElements(ExpressionRPN[i]);
            StackTree.push(te);
        }
        else if (ExpressionRPN[i] == '*' || ExpressionRPN[i] == '-' || ExpressionRPN[i] == '+' || ExpressionRPN[i] == '/')
        {
            te = CreateTreeElements(ExpressionRPN[i]);
            te -> RightPart = StackTree.top();
            StackTree.pop();
            te -> LeftPart = StackTree.top();
            StackTree.pop();
            StackTree.push(te);
        }
    }
    return StackTree.top();
}

void PrintingBinaryTree(TreeElements* Tree, int var)
{
    int i;
    if (Tree != nullptr)
    {
        PrintingBinaryTree(Tree -> RightPart, var + 1);

        for (i = 1; i <= var; i++)
        {
            cout << "   ";
        }
        cout << "|" << Tree -> temp << "|" << endl;
        PrintingBinaryTree(Tree -> LeftPart, var + 1);
    }
}

string CleaningTrash(string GlobalTemp) // ЧИСТИТ ВЕСЬ ТРЭШ !
{
    cout << GlobalTemp << endl;
    for (int j = 0; j < 2; j++)
    {
        for (int i = 0; i < GlobalTemp.length(); i ++)
        {
            if (GlobalTemp[GlobalTemp.length()-1] == '0' && (GlobalTemp[GlobalTemp.length()-2] == '+' || GlobalTemp[GlobalTemp.length()-2] == '-') )
            {
                GlobalTemp.pop_back();
                GlobalTemp.pop_back();
            }
            else if (GlobalTemp[0] == '0' && (GlobalTemp[1] == '+' || GlobalTemp[1] == '-') )
            {
                GlobalTemp.erase(0,2);
            }
            else if (GlobalTemp[i] == '0' && (GlobalTemp[i-1] == '+' || GlobalTemp[i-1] == '-'))
            {
                GlobalTemp.erase(i-1,2);
            }
            else if (GlobalTemp[0] == '1' && GlobalTemp[1] == '*')
            {
                GlobalTemp.erase(0,2);
            }
            else if (GlobalTemp[GlobalTemp.length()-1] == '1' && GlobalTemp[GlobalTemp.length()-2] == '*')
            {
                GlobalTemp.pop_back();
                GlobalTemp.pop_back();
            }
            else if (GlobalTemp[i] == '1' && GlobalTemp[i+1] == '*')
            {
                GlobalTemp.erase(i,2);
            }
            else if (GlobalTemp[i] == '1' && GlobalTemp[i-1] == '*')
            {
                GlobalTemp.erase(i-1,2);
            }
            else if (GlobalTemp[0] == '0' && GlobalTemp[1] == '*' && GlobalTemp[2] == '(' && GlobalTemp[GlobalTemp.length()-1] == ')')
            {
                GlobalTemp.erase(1, GlobalTemp.length()-1);
            }
            else if (GlobalTemp[i] == '0' && GlobalTemp[i-1] == '*' && GlobalTemp[i-2] == ')' && GlobalTemp[0] == '(')
            {
                GlobalTemp.erase(0, GlobalTemp.length()-1);
            }
        }
        GlobalTemp = GlobalTemp;
    }

    cout << GlobalTemp << endl;
    return GlobalTemp;
}