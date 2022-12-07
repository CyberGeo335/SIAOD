#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Dictionary
{
	char eng_word[255];
	char rus_word[255];
};
class BinFile
{
public:
	static int txt_to_bin(string txt_file, string bin_file);
	static Dictionary get_class(string filename, int position);
	static void AddToBin(ofstream& bin_file, Dictionary Dictionary);
	static Dictionary linear_search(string txt_file, string key);
	static string* getwords(string txt_file);

};
