#pragma once

#include <vector>
#include <queue>

#include "deps/list_sort.h"

using namespace std;

namespace string_algorithms
{
	int _raw_task9(const vector<pair<int, int>>& indexed_list, int to_find, int l = 0, int r = -1)
	{
		if (r == -1) r = indexed_list.size() - 1;
		while (true)
		{
			int middle = l + (r - l) * (to_find - indexed_list[l].first) /
				(indexed_list[r].first - indexed_list[l].first);
			if (to_find < indexed_list[middle].first) r = middle - 1;
			else if (to_find > indexed_list[middle].first) l = middle + 1;
			else return indexed_list[middle].second;

			if (indexed_list[l].first > to_find || indexed_list[r].first < to_find || l > r)
				return -1;
		}
	}

	int task9(const vector<int>& list, int to_find, int l = 0, int r = -1)
	{
		vector<pair<int, int>> indexed_list = sort_list(list);
		return _raw_task9(indexed_list, to_find, l, r);
	}
}