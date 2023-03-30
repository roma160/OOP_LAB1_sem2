#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

namespace string_algorithms
{
	// https://stackoverflow.com/questions/35974402/reading-getline-from-cin-into-a-stringstream-c
	string read_string(string name)
	{
		cout << "Enter string " << name << " : ";
		string ret;
		getline(cin, ret);
		return ret;
	}

	vector<int> read_sequence(string name)
	{
		cout << "Enter numerical sequence " << name << "\n(space is delimiter) : ";
		string inp;
		getline(cin, inp);
		stringstream ss(inp);
		vector<int> ret((istream_iterator<int>(ss)), istream_iterator<int>());
		return ret;
	}

	int read_int(string name, bool use_prompt = true)
	{
		if (use_prompt) cout << "Enter int " << name << " ";
		cout << ": ";
		string inp;
		getline(cin, inp);
		stringstream ss(inp);
		int ret;
		ss >> ret;
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
		return read_int("", false) - 1;
	}
}