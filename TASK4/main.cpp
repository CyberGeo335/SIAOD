#include "BinaryTree.h"
int main()
{

    string GlobalTemp;

    Menu();

    int menu;

    TreeElements* TreeExpression;

    while (true)
    {
        cout << "Введите номер операции: " << endl;
        cin >> menu;
        if (menu == 1)
        {
            cout << "Введите выражение: " << endl;
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
            cout << "Вывод дерева: " << endl;
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
            cout<< "Завершение работы. Хорошего дня :) ";
            exit(1);
        }
        else
        {
            cout<< "Неверный номер операции !!! :( ";
        }

    }
    return 0;
}
