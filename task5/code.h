#pragma once

#include <string>
#include <vector>

#include "deps/input.h"

using namespace std;

namespace string_algorithms
{
	vector<int> task5_lis(vector<int> a)
	{
        int n = a.size();
        vector<int> d(n+1, INT32_MAX);
        vector<int> pos(n+1);
        vector<int> prev(n);
        int length = 0;

		pos[0] = -1;
        d[0] = INT32_MIN;
        for (int i = 0; i < n; i++) {
            int l = 0, r = n;
            while(l+1 < r)
            {
                int m = (l + r) / 2;
                if (d[m] < a[i]) l = m;
                else if (d[m] > a[i]) r = m;
                else l = r = m;
            }
            int j = d[l] > d[i] ? l : r;

            if (d[j - 1] < a[i] and a[i] < d[j]){
                d[j] = a[i];
                pos[j] = i;
                prev[i] = pos[j - 1];
                length = max(length, j);
            }
        }

        vector<int> answer;
        int p = pos[length];
        while(p != -1){
            answer.push_back(a[p]);
            p = prev[p];
		}
        reverse(answer.begin(), answer.end());

        return answer;
	}

    int task5_lcs(vector<int> x, vector<int> y)
	{
        int n = x.size();
        int m = y.size();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= m; j++)
                if (x[i - 1] == y[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        return dp[n][m];
	}

    void test_task5()
	{
        int index = select_prompt({
            "lis", "lcs"
            });
        if (index == 0) {
            cout << "Computing lis\n";
            vector<int> a = read_sequence("a");
            cout << "Answer: " << sequence_to_string(task5_lis(a));
        }
        else if(index == 1){
            cout << "Computing lcs\n";
            vector<int> x = read_sequence("x");
            vector<int> y = read_sequence("y");
            cout << "Answer: " << task5_lcs(x, y);
		}
	}
}