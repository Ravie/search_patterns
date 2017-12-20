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
int manhattan_tourist(vector<vector<int>> &, vector<vector<int>> &, vector<vector<int>> &, int, int);
void LCS(string &, string &, vector<vector<int>> &, vector<vector<char>> &);
void printLCS(vector<vector<char>> &, string, string &, int, int);
void homework5(ifstream &, ofstream &);
void build_dir_sc_tables(const vector<char> &, const vector<vector<int>> &, string &, string &, vector<vector<int>> &, vector<vector<char>> &);
int score(const vector<char> &, const vector<vector<int>> &, const char, const char);
void print_alignment(const vector<vector<char>> &, const string, const string, const int, const int, string &, string &);

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
	case 5:
	{
		homework5(input_file, output_file);
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
		// разбор размерности сетки
		string inp_str1, n, m, temp;
		int height, width, max_path;

		getline(input_file, inp_str1);
		istringstream iss(inp_str1);
		getline(iss, n, ' ');
		getline(iss, m);
		height = stoi(n);
		width = stoi(m);
		// разбор массивов
		vector<string> array1, array2;
		vector<vector<int>> south_weights(height, vector<int>(width + 1));
		vector<vector<int>> east_weights(height + 1, vector<int>(width));
		// разбор первого массива
		for (int i = 0; i < height; i++)
		{
			getline(input_file, inp_str1);
			istringstream iss(inp_str1);
			for (int j = 0; j < width + 1; j++)
			{
				getline(iss, temp, ' ');
				south_weights[i][j] = stoi(temp);
			}
		}
		// считывание разделителя
		getline(input_file, inp_str1);
		// разбор второго массива
		for (int i = 0; i < height + 1; i++)
		{
			getline(input_file, inp_str1);
			istringstream iss(inp_str1);
			for (int j = 0; j < width; j++)
			{
				getline(iss, temp, ' ');
				east_weights[i][j] = stoi(temp);
			}
		}
		vector<vector<int>> edge_weight(height + 1, vector<int>(width + 1));
		max_path = manhattan_tourist(edge_weight, south_weights, east_weights, height, width);
		output_file << max_path;
	}
	break;
	case 3:
	{
		string v, w, o = "";

		getline(input_file, v);
		getline(input_file, w);
		vector<vector<int>> s(v.size() + 1, vector<int>(w.size() + 1));
		vector<vector<char>> b(v.size() + 1, vector<char>(w.size() + 1));
		LCS(v, w, s, b);
		printLCS(b, v, o, v.size(), w.size());
		output_file << o;
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

int manhattan_tourist(vector<vector<int>>&edge_weight, vector<vector<int>>&south_weights, vector<vector<int>>&east_weights, int height, int width)
{
	edge_weight[0][0] = 0;
	for (int i = 1; i <= height; i++)
	{
		edge_weight[i][0] = edge_weight[i - 1][0] + south_weights[i - 1][0];
		cout << edge_weight[i][0] << endl;
	}
	cout << endl;
	for (int j = 1; j <= width; j++)
	{
		edge_weight[0][j] = edge_weight[0][j - 1] + east_weights[0][j - 1]; 
		cout << edge_weight[0][j] << " ";
	}
	cout << endl;
	for (int i = 1; i <= height; i++)
	{
		for (int j = 1; j <= width; j++)
		{
			edge_weight[i][j] = max(edge_weight[i - 1][j] + south_weights[i - 1][j], edge_weight[i][j - 1] + east_weights[i][j - 1]);
			cout << edge_weight[i][j] << " ";
		}
		cout << endl;
	}
	return edge_weight[height][width];
}

void LCS(string &v, string &w, vector<vector<int>> &s, vector<vector<char>> &b)
{
	int n = v.size();
	int m = w.size();
	for (int i = 0; i <= n; i++)
	{
		s[i][0] = 0;
	}
	for (int j = 0; j <= m; j++)
	{
		s[0][j] = 0;
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			if (v[i - 1] == w[j - 1])
			{
				s[i][j] = max(max(s[i - 1][j], s[i][j - 1]), s[i - 1][j - 1] + 1);
			}
			else
			{
				s[i][j] = max(s[i - 1][j], s[i][j - 1]);
			}
			if (s[i][j] == s[i - 1][j])
			{
				b[i][j] = '^';
			}
			else if (s[i][j] == s[i][j - 1])
			{
				b[i][j] = '<';
			}
			else if (s[i][j] == s[i - 1][j - 1] + 1)
			{
				b[i][j] = '\\';
			}
			//cout << b[i][j] << " ";
		}
		//cout << endl;
	}
}

void printLCS(vector<vector<char>> &b, string v, string &o, int i, int j)
{
	if (i == 0 || j == 0)
	{
		return;
	}
	if (b[i][j] == '\\')
	{
		printLCS(b, v, o, i - 1, j - 1);
		o += v[i - 1];
	}
	else
	{
		if (b[i][j] == '^')
		{
			printLCS(b, v, o, i - 1, j);
		}
		else
		{
			printLCS(b, v, o, i, j - 1);
		}
	}
}

void homework5(ifstream &input_file, ofstream &output_file)
{
	int tasknum;
	cout << "Choose task number: ";
	cin >> tasknum;
	switch (tasknum)
	{
	case 1:
	{
		string inp_str1, inp_str2, inp_str3, temp, out_str1, out_str2;
		// разбираем 2 последовательности аминокислот
		getline(input_file, inp_str1);
		getline(input_file, inp_str2);
		// выделяем место под таблицы весов и направлений
		vector<vector<int>> score_table(inp_str1.size() + 1, vector<int>(inp_str2.size() + 1));
		vector<vector<char>> direction_table(inp_str1.size() + 1, vector<char>(inp_str2.size() + 1));
		// разбираем таблицу BLOSUM62
		ifstream blosum_file;
		blosum_file.open("blosum62.txt");
		// считываем последовательность аминокислот в таблице
		vector<char> acids;
		getline(blosum_file, inp_str3);
		for (int i = 0; i < inp_str3.size(); i++)
		{
			if (inp_str3[i] != ' ')
			{
				acids.push_back(inp_str3[i]);
			}
		}
		// считываем саму таблицу
		vector<vector<int>> blosum62(acids.size() + 1, vector<int>(acids.size() + 1));
		for (int i = 1; i <= acids.size(); i++)
		{
			getline(blosum_file, inp_str3);
			istringstream iss(inp_str3);
			for (int j = 1; j <= acids.size(); j++)
			{
				getline(iss, temp, ' ');
				while (temp == "")
				{
					getline(iss, temp, ' ');
				}
				blosum62[i][j] = stoi(temp);
			}
		}
		blosum_file.close();
		// строим таблицы весов и направлений
		build_dir_sc_tables(acids, blosum62, inp_str1, inp_str2, score_table, direction_table);
		// делаем выравнивание обеих последовательностей
		print_alignment(direction_table, inp_str1, inp_str2, inp_str1.size(), inp_str2.size(), out_str1, out_str2);
		output_file << score_table[inp_str1.size()][inp_str2.size()] << endl << out_str1 << endl << out_str2;
		for (int i = 0; i <= inp_str1.size(); i++)
		{
			for (int j = 0; j <= inp_str2.size(); j++)
			{
				cout << score_table[i][j] << " ";
			}
			cout << endl;
		}
	}
	break;
	case 2:
	{

	}
	break;
	default:
	{
		cout << "Incorrect number";
	}
	}
}

void build_dir_sc_tables(const vector<char> &acid, const vector<vector<int>> &substitution_matrix, string &v, string &w, vector<vector<int>> &score_table, vector<vector<char>> &direction_table)
{
	int n = v.size();
	int m = w.size();
	for (int i = 0; i <= n; i++)
	{
		score_table[i][0] = -5 * i;
		direction_table[i][0] = '^';
	}
	for (int j = 0; j <= m; j++)
	{
		score_table[0][j] = -5 * j;
		direction_table[0][j] = '<';
	}
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			score_table[i][j] = max(max(score_table[i - 1][j] - 5, score_table[i][j - 1] - 5), score_table[i - 1][j - 1] + score(acid, substitution_matrix, v[i - 1], w[j - 1]));
			if (score_table[i][j] == score_table[i - 1][j] - 5)
			{
				direction_table[i][j] = '^';
			}
			else if (score_table[i][j] == score_table[i][j - 1] - 5)
			{
				direction_table[i][j] = '<';
			}
			else if (score_table[i][j] == score_table[i - 1][j - 1] + score(acid, substitution_matrix, v[i - 1], w[j - 1]))
			{
				direction_table[i][j] = '\\';
			}
			cout << direction_table[i][j] << " ";
		}
		cout << endl;
	}
}

int score(const vector<char> &acid, const vector<vector<int>> &substitution_matrix, const char v, const char w)
{
	int x = 0, y = 0;
	for (int i = 0; i < acid.size(); i++)
	{
		if (v == acid[i])
		{
			x = i;
		}
		if (w == acid[i])
		{
			y = i;
		}
	}
	return substitution_matrix[x + 1][y + 1];
}

void print_alignment(const vector<vector<char>> &direction_table, const string v_in, const string w_in, const int i, const int j, string &v_out, string &w_out)
{
	if (i == 0 && j == 0)
	{
		return;
	}
	if (direction_table[i][j] == '\\')
	{
		print_alignment(direction_table, v_in, w_in, i - 1, j - 1, v_out, w_out);
		v_out += v_in[i - 1];
		w_out += w_in[j - 1];
	}
	else if (direction_table[i][j] == '^')
	{
		print_alignment(direction_table, v_in, w_in, i - 1, j, v_out, w_out);
		v_out += v_in[i - 1];
		w_out += "-";
	}
	else if (direction_table[i][j] == '<')
	{
		print_alignment(direction_table, v_in, w_in, i, j - 1, v_out, w_out);
		v_out += "-";
		w_out += w_in[j - 1];
	}
}
