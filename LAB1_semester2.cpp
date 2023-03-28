#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9B%D0%B0%D0%BD%D0%B4%D0%B0%D1%83-%D0%92%D0%B8%D1%88%D0%BA%D0%B8%D0%BD%D0%B0_(k_%D1%80%D0%B0%D0%B7%D0%BB%D0%B8%D1%87%D0%B8%D0%B9)

int main()
{
    string x("abcde");
    string y("aceabpcqdeabcr");
    int m = x.size();
    int n = y.size();
    int k = 2;
    vector<vector<int>> r(m + n + 1, vector<int>(k + 2));
    vector<int> res;
    for (int p = 0; p <= n; p++)
        r[p + m][0] = -1;
    for (int p = -k - 1; p <= -1; p++)
    {
        r[p + m][-p] = -p - 1;
        r[p + m][-p - 1] = -p - 2;
    }
    for (int q = -1; q <= k; q++)
        r[n + m + 1][q + 1] = -1;
    for (int q = 0; q <= k; q++)
    {
	    for (int p = -q; p <= n; p++)
	    {
            int R = max(
                r[p + m][q] + 1,
                max(
                r[p - 1 + m][q],
                r[p + 1 + m][q] + 1
                )
            );
            R = min(R, m);
            while (R < m && R + p < n && x[R + 1] == y[R + 1 + p]) R++;
            r[p + m][q + 1] = R;
            if (r[p + m][q + 1] == m)
                res.push_back(p + m);
	    }
    }

    cout << x << "\n" << y << "\n\n";
    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i] << "\n";
    }
}