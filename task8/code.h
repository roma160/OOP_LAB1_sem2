#pragma once

#include <vector>
#include <queue>

#include "deps/list_sort.h"

using namespace std;

namespace string_algorithms
{
	int _raw_task8(const vector<pair<int, int>>& indexed_list, int to_find)
	{
		int l = 0, r = indexed_list.size() - 1;
		while (true)
		{
			int middle = (l + r) / 2;
			if (to_find < indexed_list[middle].first) r = middle - 1;
			else if (to_find > indexed_list[middle].first) l = middle + 1;
			else return indexed_list[middle].second;

			if (l > r) return -1;
		}
	}

	int task8(const vector<int>& list, int to_find)
	{
		vector<pair<int, int>> indexed_list = sort_list(list);
		return _raw_task8(indexed_list, to_find);
	}
}