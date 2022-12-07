#include "BinFile.h"

int BinFile::txt_to_bin(string txt_file, string bin_file)
{
	ifstream inp;
	inp.open(txt_file, ios::binary || ios::app);
	ofstream outp;
	outp.open(bin_file, ios::binary || ios::app);
	if (inp.good() && outp.good())
	{
		Dictionary tt;
		while (true)
		{
			inp >> tt.eng_word;
			if (!inp.eof())
			{
				inp >> tt.rus_word;
				outp.write((char*)&tt, sizeof(Dictionary));
			}
			else break;
		}
		inp.close();
		outp.close();
		return 1;
	}
	else
	{
		inp.close();
		outp.close();
		return 0;
	}

}
Dictionary BinFile::get_class(string filename, int position)
{
	Dictionary tt;
	ifstream bin_file(filename, ios::binary | ios::in);
	bin_file.seekg((position) * sizeof(tt));
	bin_file.read((char*)&tt, sizeof(Dictionary));
	bin_file.close();
	return tt;
}
void BinFile::AddToBin(ofstream& bin_file, Dictionary Dictionary)
{
	bin_file.seekp(0, ios::end);
	bin_file.write((char*)&Dictionary, sizeof(Dictionary));
}
Dictionary BinFile::linear_search(string bin_file, string key)
{
	ifstream inp;
	inp.open(bin_file, ios::binary || ios::app);
	Dictionary tt;
	tt.eng_word[0] = ' ';
	while (true)
	{
		inp.read((char*)&tt, sizeof(tt));
		if (!inp.eof())
		{
			if (tt.eng_word == key)
			{
				return tt;
			}
		}
		else
		{
			break;
		}
	}
	inp.close();
	return tt;
}
string* BinFile::getwords(string txt_file)
{
	ifstream inp;
	inp.open(txt_file, ios::binary || ios::app);
	Dictionary tt;
	string *words= new string[10000];
	int i = 0;
	while (true)
	{
		inp.read((char*)&tt, sizeof(tt));
		if (!inp.eof())
		{
			words[i] = tt.eng_word;
			i++;
		}
		else
		{
			break;
		}
	}
	inp.close();
	return words;
}