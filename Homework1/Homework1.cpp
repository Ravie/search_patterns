// Homework1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
using namespace std;

string reverse_complement(string);
string find_patterns(string, string);
int count_patterns(string, string);
string frequent_patterns(string, int);
void homework1(ifstream &, ofstream &);
void homework4(ifstream &, ofstream &);
int coins_exchange(int, vector<int> &);

int main()
{
	ifstream input_file;
	input_file.open("input.txt");
	ofstream output_file;
	output_file.open("output.txt");

	int switcher;
	cout << "Choose homework number: ";
	cin >> switcher;
	switch (switcher)
	{
	case 1:
	{
		homework1(input_file, output_file);
	}
	break;
	case 4:
	{
		homework4(input_file, output_file);
	}
	break;
	default:
	{
		cout << "Incorrect number";
	}
	}

	input_file.close();
	output_file.close();
    return 0;
}

string reverse_complement(string str)
{
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == 'A')
			str[i] = 'T';
		else if (str[i] == 'T')
			str[i] = 'A';
		else if (str[i] == 'G')
			str[i] = 'C';
		else if (str[i] == 'C')
			str[i] = 'G';
	}
	reverse(str.begin(), str.end());
	return str;
}

string find_patterns(string substr, string str)
{
	string positions;
	int i = 0;
	for (i = str.find(substr, i++); i != string::npos; i = str.find(substr, i + 1))
	{
		positions += to_string(i) + " ";
	}
	return positions;
}

int count_patterns(string str, string substr)
{
	int i = 0, cnt = 0;
	for (i = str.find(substr, i++); i != string::npos; i = str.find(substr, i + 1))
	{
		cnt++;
	}
	return cnt;
}


string frequent_patterns(string str, int size)
{
	string result, tmp;
	int i, max = 0, cnt = 0;
	for (i = 0; i < str.length() - size; i++)
	{
		cnt = count_patterns(str, str.substr(i, size));
		if (cnt > max)
		{
			result = str.substr(i, size) + " ";
			max = cnt;
		}
		else if (cnt == max)
		{
			if (!count_patterns(result, str.substr(i, size)))
			{
				result += str.substr(i, size) + " ";
			}
		}
	}
	return result;
}

void homework1(ifstream &input_file, ofstream &output_file)
{
	int tasknum;
	cout << "Choose task number: ";
	cin >> tasknum;
	switch (tasknum)
	{
	case 1:
	{
		string input_str, output_str;

		getline(input_file, input_str);
		//cout << input_str << endl;
		output_str = reverse_complement(input_str);
		//cout << output_str << endl;
		output_file << output_str;
	}
	break;
	case 2:
	{
		string pattern, genome, output_str;

		getline(input_file, pattern);
		getline(input_file, genome);
		output_str = find_patterns(pattern, genome);
		//cout << output_str << endl;
		output_file << output_str;
	}
	break;
	case 3:
	{
		string pattern, genome, output_str;

		getline(input_file, genome);
		getline(input_file, pattern);
		output_str = to_string(count_patterns(genome, pattern));
		//cout << output_str << endl;
		output_file << output_str;
	}
	break;
	case 4:
	{
		string length, genome, output_str;
		int mer_length;

		getline(input_file, genome);
		getline(input_file, length);
		mer_length = stoi(length);
		output_str = frequent_patterns(genome, mer_length);
		//cout << output_str << endl;
		output_file << output_str;
	}
	break;
	default:
	{
		cout << "Incorrect number";
	}
	}
}

void homework4(ifstream &input_file, ofstream &output_file)
{
	int tasknum;
	cout << "Choose task number: ";
	cin >> tasknum;
	switch (tasknum)
	{
	case 1:
	{
		string inp_str1, inp_str2, token;
		int amount, min_coins;
		vector<int> denoms;

		getline(input_file, inp_str1);
		getline(input_file, inp_str2);
		istringstream iss(inp_str2);
		amount = stoi(inp_str1);
		while (getline(iss, token, ','))
		{
			denoms.push_back(stoi(token));
		}
		cout << amount << endl;
		min_coins = coins_exchange(amount, denoms);
		cout << min_coins << endl;
		output_file << min_coins;
	}
	break;
	case 2:
	{

	}
	break;
	case 3:
	{

	}
	break;
	case 4:
	{

	}
	break;
	default:
	{
		cout << "Incorrect number";
	}
	}
}
/*
void parser(string str, vector<int> &denoms)
{
	char *s = new char[str.size() + 1];

	strcpy(s, str.c_str());

	char *p = strtok(s, ",");

	while (p != NULL) {
		denoms.push_back(atoi(p));
		p = strtok(NULL, ",");
	}
	reverse(denoms.begin(), denoms.end());

	delete[] s;
}
*/
int coins_exchange(int sum, vector<int> &denom)
{
	int *bestNumCoins = new int[sum + 1];
	int m, i;
	bestNumCoins[0] = 0;
	for (m = 1; m <= sum; m++)
	{
		bestNumCoins[m] = INT_MAX;
		for (i = 0; i < denom.size(); i++)
		{
			if (m >= denom[i])
			{
				if (bestNumCoins[m - denom[i]] + 1 < bestNumCoins[m])
				{
					bestNumCoins[m] = bestNumCoins[m - denom[i]] + 1;
				}
			}
		}
	}
	return bestNumCoins[sum];
}
