#include "BinaryTree.h"
int main()
{

    string GlobalTemp;

    Menu();

    int menu;

    TreeElements* TreeExpression;

    while (true)
    {
        cout << "������ ����� ����樨: " << endl;
        cin >> menu;
        if (menu == 1)
        {
            cout << "������ ��ࠦ����: " << endl;
            string Expression;
            cin.get();
            getline(cin, Expression);
            GlobalTemp = Expression;
            Expression = ExpressionToRPN(Expression);
            cout << Expression << endl;
            TreeExpression = ParserRPN(Expression);

        }
        else if (menu == 2)
        {
            cout << "�뢮� ��ॢ�: " << endl;
            PrintingBinaryTree(TreeExpression, 0);

        }
        else if (menu == 3)
        {
            string Minimization = CleaningTrash(GlobalTemp);
            Minimization = ExpressionToRPN(Minimization);
            TreeExpression = ParserRPN(Minimization);
            PrintingBinaryTree(TreeExpression, 0);
        }
        else if (menu == 4)
        {
            cout<< "�����襭�� ࠡ���. ���襣� ��� :) ";
            exit(1);
        }
        else
        {
            cout<< "������ ����� ����樨 !!! :( ";
        }

    }
    return 0;
}
