#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace string_algorithms
{
	string read_string(string name)
	{
		cout << "Enter string " << name << " : ";
		string ret = "";
		while(ret.empty())
			getline(cin, ret);
		return ret;
	}

	vector<int> read_sequence(string name)
	{
		cout << "Enter sequence " << name << " : ";
		string inp = "";
		while (inp.empty())
			getline(cin, inp);
		stringstream ss(inp);
		vector<int> ret((istream_iterator<int>(ss)), istream_iterator<int>());
		return ret;
	}

	int read_int(string name)
	{
		cout << "Enter int " << name << " : ";
		int ret;
		cin >> ret;
		return ret;
	}

	string sequence_to_string(vector<int> a)
	{
		stringstream ss;
		for (auto el : a) ss << el << " ";
		return ss.str();
	}

	int select_prompt(vector<string> options)
	{
		cout << "Select one of the options:\n";
		for (int i = 0; i < options.size(); i++)
			cout << "   " << i + 1 << ". " << options[i]<<"\n";
		cout << ": ";
		int ret;
		cin >> ret;
		return ret - 1;
	}
}