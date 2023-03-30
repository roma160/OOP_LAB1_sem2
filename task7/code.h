#pragma once

#include <vector>
#include <queue>

using namespace std;

namespace string_algorithms
{
	vector<int> task7(vector<int> a, vector<int> b)
	{
		sort(a.begin(), a.end());
		sort(b.begin(), b.end());
		int n = a.size(), m = b.size();
		int i = 0, j = 0;

		vector<int> ret;
		while(i < n && j < m)
		{
			if (a[i] < b[j]) i++;
			else if (a[i] > b[j]) j++;
			else
			{
				ret.push_back(a[i]);
				i++; j++;
			}
		}

		return ret;
	}

	void test_task7()
	{
		vector<int> a = read_sequence("a");
		vector<int> b = read_sequence("b");
		cout << "Common elements of a and b : " << sequence_to_string(task7(a, b));
	}
}