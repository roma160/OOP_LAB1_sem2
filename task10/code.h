#pragma once

#include <vector>
using namespace std;

namespace string_algorithms
{
	int task10(const vector<int>& list, int to_find, int guess_index)
	{
		// Exit on wrong input
		if (to_find < list[0] || to_find > list[list.size() - 1])
			return -1;
		if (guess_index < 0 || guess_index >= list.size())
			return task8(list, to_find);

		// Algorithm starts
		int l = guess_index, r = guess_index;
		int inc = 1;
		if(to_find >= list[r]) while (true)
		{
			r += inc;
			if(r >= list.size() - 1)
				return task8(list, to_find, l);
			if (list[r] > to_find) break;
			l = r;
			inc <<= 1;
		}
		else while (true)
		{
			l -= inc;
			if (l <= 0)
				return task8(list, to_find, 0, r);
			if (list[l] <= to_find) break;
			r = l;
			inc <<= 1;
		}

		return task8(list, to_find, l, r);
	}

	void test_task10()
	{
		vector<int> list = read_sequence("list");
		int to_find = read_int("to_find");
		int guess_index = read_int("guess_index");
		cout << "Index of to_find (zero indexed) : " << task10(list, to_find, guess_index);
	}
}