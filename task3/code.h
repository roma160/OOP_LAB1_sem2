#pragma once

#include <string>
#include <vector>
#include <set>

using namespace std;

namespace string_algorithms
{
	/// <returns> true if x is in y </returns>
	bool task3(const string& y, const string& x)
	{
		int n = y.size() - 1;
		int m = x.size() - 1;
		while (n >= 0 && m >= 0)
		{
			if(x[m] != y[n])
			{
				n--;
				continue;
			}

			// x[m] == y[n]
			m--;
			n--;
		}
		return m == -1;
	}
}