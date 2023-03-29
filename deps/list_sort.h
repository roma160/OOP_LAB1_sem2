#pragma once

#include <vector>
#include <queue>

using namespace std;

namespace string_algorithms
{
	vector<pair<int, int>> sort_list(const vector<int>& list)
	{
		vector<pair<int, int>> indexed_list(list.size());
		for (int i = 0; i < list.size(); i++)
			indexed_list[i] = move(pair<int, int>{ list[i], i });
		sort(indexed_list.begin(), indexed_list.end(),
			[](auto a, auto b) { return a.first < b.first; });
		return indexed_list;
	}
}