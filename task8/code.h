#pragma once

#include <vector>

using namespace std;

namespace string_algorithms
{
	int task8(const vector<int>& list, int to_find, int l = 0, int r = -1)
	{
		if (r == -1) r = list.size() - 1;
		while (true)
		{
			int middle = (l + r) / 2;
			if (to_find < list[middle]) r = middle - 1;
			else if (to_find > list[middle]) l = middle + 1;
			else return middle;

			if (l > r) return -1;
		}
	}

	void test_task8()
	{
		vector<int> list = read_sequence("list");
		int to_find = read_int("to_find");
		int l = read_int("left (enter -1 for default val)");
		if (l == -1) l = 0;
		int r = read_int("left (enter -1 for default val)");
		cout << "Index of to_find (zero indexed) : " << task8(list, to_find, l, r);
	}
}