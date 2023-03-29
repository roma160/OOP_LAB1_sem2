#pragma once

#include <vector>
using namespace std;

namespace string_algorithms
{
	int task10(const vector<int>& list, int to_find, int guess_index)
	{
		// Prepatations
		//vector<pair<int, int>> indexed_list = sort_list(list);
		//for(int i = 0; i < indexed_list.size(); i++)
		//	if(indexed_list[i].second == guess_index)
		//	{
		//		guess_index = i;
		//		break;
		//	}

		//// Exit on wrong input
		//if (to_find < indexed_list[0].first || to_find > indexed_list[indexed_list.size() - 1].first)
		//	return -1;
		//if (guess_index < 0 || guess_index >= indexed_list.size())
		//	return _raw_task8(indexed_list, to_find);

		//// Algorithm starts
		//int l = guess_index, r = guess_index;
		//int inc = 1;
		//if(to_find >= indexed_list[r].first)
		//	while (to_find >= indexed_list[r].first)
		//	{
		//		r += inc;
		//		if(r >= indexed_list.size())
		//			return _raw_task8(indexed_list, to_find);

		//	}

		return 0;
	}
}