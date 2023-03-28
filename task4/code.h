#pragma once

#include <string>
#include <vector>

using namespace std;

namespace string_algorithms
{
	int levenshtein_metric(char a, char b)
	{ return a != b; }

	int min(int a, int b)
	{ return a <= b ? a : b; }

	/// <summary>
	/// Computes Levenshtein distance from a to b
	/// </summary>
	int task4(const string& a, const string& b, int (*w)(char, char) = levenshtein_metric)
	{
		int n = a.size();
		int m = b.size();
		vector<vector<int>> d(n+1, vector<int>(m+1));

		// Initial values
		d[0][0] = w(0, 0);
		for (int i = 1; i <= n; i++)
			d[i][0] = w(a[i-1], 0);
		for (int i = 1; i <= m; i++)
			d[0][i] = w(0, b[i - 1]);

		// Recurrent formula
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				d[i][j] = min(
					d[i - 1][j] + w(a[i - 1], 0),
					min(
						d[i][j - 1] + w(0, b[j - 1]),
						d[i - 1][j - 1] + w(a[i - 1], b[j - 1])
					)
				);
			}

		return d[n][m];
	}
}