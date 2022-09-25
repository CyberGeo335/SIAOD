#include <iostream>

using namespace std;

int Task1(unsigned int x, unsigned int mask);
int Task2(unsigned int x, unsigned int mask);
int Task3(unsigned int x);
int Task4(unsigned int x);
int Task5(unsigned int temp, unsigned int x);
int Mask5(unsigned int mask, unsigned int n);
void coutp(unsigned int x);

void coutp(unsigned int x)
{
    unsigned int n = sizeof(int) * 8;
    unsigned  SysCount2 = (1 << (n - 1));
    cout << "Sc2: ";
    for (int i = 1; i <= n; i++)
    {
        cout << ((x & SysCount2) >> (n - i));
        SysCount2 = SysCount2 >> 1;
    }
    cout << endl;
   
}
int Task1(unsigned int x, unsigned int mask)
{
    return x | mask;
}
int Task2(unsigned int x, unsigned int mask)
{
    return x & mask;
}
int Task3(unsigned int x)
{
    return x << 4;
}
int Task4(unsigned int x)
{
    return x >> 4;
}
int Mask5(unsigned int mask, unsigned int n)
{
    unsigned int temp = 32 - n - 1;
    return mask = mask >> temp;
}
int Task5(unsigned int temp, unsigned int x)
{
    return x = x | temp;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "=====================================" << endl;
    cout << "Theme: Bitwise Operations" << endl;
    cout << "Task 1: Четыре младших бита превратить в 1;" << endl;
    cout << "Task 2: Обнулить заданные биты исходного значения целочисленной переменной, введенной пользователем;" << endl;
    cout << "Task 3: Умножить значение целочисленной переменной;" << endl;
    cout << "Task 4: Разделить значение целочисленной переменной;" << endl;
    cout << "Task 5: Ввести число с клавиатуры и номер бита, который нужно превратить в 1;" << endl;
    cout << "Enter your task: ";
    int task;
    cin >> task;
    if (task == 1)
    {
        cout << "Your task is " << task << endl;
        unsigned int x = 17;
        cout << "Your number in sc10: " << x << endl;
        coutp(x);
        unsigned int mask = 0xF;
        cout << "Your mask in sc10: " << mask << endl;
        coutp(mask);
        cout << "Your result is: " << Task1(x, mask)<<endl;
        unsigned int result = Task1(x, mask);
        coutp(result);
    }
    else if (task == 2)
    {
        cout << "Your task is " << task << endl;
        unsigned int x;
        cout << "Enter your number: ";
        cin >> x;
        coutp(x);
        unsigned int mask = 0xFFFFF7D7;
        cout << "Your mask in sc10: " << mask << endl;
        coutp(mask);
        cout << "Your result is: " << Task2(x, mask) << endl;
        unsigned int result = Task2(x, mask);
        coutp(result);
    }
    else if (task == 3)
    {
        cout << "Your task is " << task << endl;
        unsigned int x;
        cout << "Enter your number: ";
        cin >> x;
        coutp(x);
        cout << "Number * 16: " << x * 16 << endl;
        cout << "Your result is: "<< Task3(x) << endl;
        unsigned int result = Task3(x);
        coutp(result);
    }
    else if (task == 4)
    {
        cout << "Your task is " << task << endl;
        unsigned int x;
        cout << "Enter your number: ";
        cin >> x;
        coutp(x);
        cout << "Number / 16: " << x / 16 << endl;
        cout << "Your result is: " << Task4(x) << endl;
        unsigned int result = Task4(x);
        coutp(result);
    }
    else if (task == 5)
    {
        cout << "Your task is " << task << endl;
        unsigned int n;
        unsigned int x;
        cout << "Enter your number: ";
        cin >> x;
        coutp(x);
        cout << "Enter your index: ";
        cin >> n;
        unsigned int mask = 0x80000000;
        unsigned int temp = Mask5(mask, n);
        cout << "Your result is: " << Task5(temp, x) << endl;
        int result = Task5(temp, x);
        coutp(result);
    }
    else
    {
        cout << "Incorrect Task. Try it again. " << endl;
    }    
}
