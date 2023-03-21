#pragma once

#include <vector>
#include <string>

using namespace std;

namespace strings_algorithms
{
	vector<int> pre(string s);
	/// <summary>
	/// The first algorithm of searching first exact substring.
	///	The link to used algorithm: http://algolist.ru/search/esearch/kmp.php
	/// </summary>
	/// <returns>Index of the first char of substring</returns>
	int task1(const string &s, const string &x);
}
