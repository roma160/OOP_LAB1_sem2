#pragma once

#include <vector>
#include <queue>

using namespace std;

namespace string_algorithms
{
	int task9(const vector<int>& list, int to_find, int l = 0, int r = -1)
	{
		if (r == -1) r = list.size() - 1;
		vector<pair<int, int>> indexed_list(r + 1);
		for (int i = 0; i <= r; i++)
			indexed_list[i] = move(pair<int, int>{ list[i], i });
		sort(indexed_list.begin(), indexed_list.end(),
			[](auto a, auto b) { return a.first < b.first; });

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
}