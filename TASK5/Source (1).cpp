#include"BST.h"
#include "BinFile.h"
#include "BTree.h"

using namespace std;
extern double counter;

int main()
{
	setlocale(LC_ALL, "rus");
	class node *root = NULL;
	BTree t(2);
	string txt_file, bin_file;
	string key;
	Dictionary temp;
	int adress;
	string *words/* = new string[10000]*/;
	int i = 0;
	while (true)
	{
		system("cls");
		cout << "������� ����� �������:\n1-�������� �����\n2-����� � ������� ��������� ������\n3-����� ������ �� �� ������\n4-���������� ������ � ����\n5-���������� ��������� ������ �� �����\n6-���������� �������� � ������\n7-����� �� ����� � ������\n8-�������� �������� �� ������\n9-����� ������\n10-���������� B-������ �� �����\n11-���������� �������� � ������\n12-����� �� ����� � ������\n13-�������� �������� �� ������\n14-����� ������\n����� ������ ����� ������� ���������" << endl;
		int k = 0;
		cin >> k;
		if (k == 1)
		{
			system("cls");
			cout << "�������� �����" << endl;
			cout << "������� ��� ���������� �����" << endl;
			cin >> txt_file;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			if (BinFile::txt_to_bin(txt_file, bin_file) == 1)
			{
				cout << "������� �������" << endl;
			}
			else
			{
				cout << "���� �� ����������" << endl;
			}
			system("pause");
		}
		if (k == 2)
		{
			system("cls");
			cout << "����� � ������� ��������� ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			cout << "������� ���� (���������� �����)" << endl;
			cin >> key;
			temp=BinFile::linear_search(bin_file, key);
			if (temp.eng_word[0] != ' ')
			{
				cout << temp.eng_word << " " << temp.rus_word;
			}
			else
			{
				cout <<"������ � ����� ������ �� �������" << endl;;
			}
			system("pause");
		}
		if (k == 3)
		{
			system("cls");
			cout << "����� ������ �� �� ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			cout << "������� �������" << endl;
			cin >> adress;
			temp=BinFile::get_class(bin_file, adress);
			if (temp.eng_word[0] != ' ')
			{
				cout << temp.eng_word << " " << temp.rus_word;
			}
			else
			{
				cout << "������ � ����� ������ �� �������" << endl;;
			}
			system("pause");
		}
		if (k == 4)
		{
			system("cls");
			cout << "���������� ������ � ����" << endl; 
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ofstream outp;
			outp.open(bin_file, ios::binary||ios::app);
			cout << "������� ���������� ����� ";
			cin >> temp.eng_word;
			cout << "������� ������� �����(���������� ����) ";
			cin >> temp.rus_word;
			if (outp.good())
			{
				BinFile::AddToBin(outp, temp);
			}
			else
			{
				cout << "������ ����� �� ����������" << endl;
			}
			outp.close();
			system("pause");
		}
		if (k == 5)
		{
			system("cls");
			cout << "���������� ��������� ������ �� �����" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ifstream inp;
			inp.open(bin_file, ios::binary || ios::app);
			if (inp.good())
			{
				inp.close();
				words = BinFile::getwords(bin_file);
				while (words[i] != "\0")
				{
					root = node::insert(root, words[i], i);
					i++;
				}
				cout << "�������" << endl;
				//delete[] words;
			}
			else
			{
				cout << "���� �� ����������" << endl;
			}
			system("pause");
		}
		if (k == 6)
		{
			system("cls");
			cout << "���������� �������� � ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ofstream outp;
			outp.open(bin_file, ios::binary || ios::app);

			cout << "������� ���������� ����� ";
			cin >> temp.eng_word;
			cout << "������� ������� �����(���������� ����) ";
			cin >> temp.rus_word;
			if (outp.good())
			{
				BinFile::AddToBin(outp, temp);
				root = node::insert(root, temp.eng_word, i);
				i++;
			}
			else
			{
				cout << "������ ����� �� ����������" << endl;
			}
			outp.close();
			system("pause");
		}
		if (k == 7)
		{
			system("cls");
			cout << "����� �� ����� � ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ofstream outp;
			outp.open(bin_file, ios::binary || ios::app);
			if (outp.good())
			{
				cout << "������� ����(���������� �����) ";
				cin >> key;
				adress = node::search(root, key);
				if (adress!=-1)
				{
					temp = BinFile::get_class(bin_file, adress);
					cout << temp.eng_word << " " << temp.rus_word;
				}
				else
				{
					cout << "������ � ����� ������ �� �������" << endl;
				}
			}
			else
			{
				cout << "������ ����� �� ����������" << endl;
			}
			outp.close();
			system("pause");
		}
		if (k == 8)
		{
			system("cls");
			cout << "�������� �������� �� ������" << endl;
			cout << "������� ����" << endl;
			cin >> key;
			if (node::search(root, key) != -1)
			{
				root = node::deleteNode(root, key);
				cout << "������� �������" << endl;
			}
			else
			{
				cout << "������ � ����� ������ �� �������" << endl;
			}
			system("pause");
		}
		if (k == 9)
		{
			system("cls");
			cout << "����� ������" << endl;
			cout << "����� ������ ������" << endl;
			node::printBT("", root, false, 1);
			cout << "����� �������� ������" << endl;
			node::printBT("", root, false, 0);
			system("pause");
		}
		if (k == 10)
		{
			system("cls");
			cout << "���������� B-������ �� �����" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ifstream inp;
			i = 0;
			inp.open(bin_file, ios::binary || ios::app);
			if (inp.good())
			{
				inp.close();
				words = BinFile::getwords(bin_file);
				while (words[i] != "\0")
				{
					t.insert(words[i], i);
					i++;
				}
				cout << "�������" << endl;
			}
			else
			{
				cout << "���� �� ����������" << endl;
			}
			system("pause");
		}
		if (k == 11)
		{
			system("cls");
			cout << "���������� �������� � ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ofstream outp;
			outp.open(bin_file, ios::binary || ios::app);

			cout << "������� ���������� ����� ";
			cin >> temp.eng_word;
			cout << "������� ������� �����(���������� ����) ";
			cin >> temp.rus_word;
			if (outp.good())
			{
				BinFile::AddToBin(outp, temp);
				t.insert(temp.eng_word, i);
				i++;
			}
			else
			{
				cout << "������ ����� �� ����������" << endl;
			}
			outp.close();
			system("pause");
		}
		if (k == 12)
		{
			system("cls");
			cout << "����� �� ����� � ������" << endl;
			cout << "������� ��� ��������� �����" << endl;
			cin >> bin_file;
			ofstream outp;
			outp.open(bin_file, ios::binary || ios::app);
			if (outp.good())
			{
				cout << "������� ����(���������� �����) ";
				cin >> key;
				adress = t.search(key);
				if (adress != NULL)
				{
					temp = BinFile::get_class(bin_file, adress);
					cout << temp.eng_word << " " << temp.rus_word;
				}
				else
				{
					cout << "������ � ����� ������ �� �������" << endl;
				}
			}
			else
			{
				cout << "������ ����� �� ����������" << endl;
			}
			outp.close();
			system("pause");
		}
		if (k == 13)
		{
			system("cls");
			cout << "�������� �������� �� ������" << endl;
			cout << "������� ����" << endl;
			cin >> key;
			if (t.search(key) != NULL)
			{
				t.deletion(key);
				cout << "������� �������" << endl;
			}
			else
			{
				cout << "������ � ����� ������ �� �������" << endl;
			}
			system("pause");
		}
		if (k == 14)
		{
			system("cls");
			cout << "����� ������" << endl;
			t.traverse();
			system("pause");
		}
		if (k < 1 || k>14)
		{
			cout << "�� �������, ��� ������ �����? Y/N" << endl;
			char j;
			cin >> j;
			if (j == 'Y')
			{
				cout << "�����... ";
				system("pause");
				exit(0);
			}
		}
	}
}