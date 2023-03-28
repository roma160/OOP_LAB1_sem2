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
    vector<vector<int>> r(m + n + 3, vector<int>(k + 2));
    auto get_r = [&r, m](int p, int q) -> int&
    {
        return r[p + m + 1][q + 1];
    };

    vector<int> res;
    for (int p = 0; p <= n; p++)
        get_r(p,-1) = -1;

    for (int p = -k-1; p <= -1; p++)
    {
        get_r(p, -p-1) = -p - 1;
        get_r(p, -p-2) = -p - 2;
    }

    for (int q = -1; q <= k; q++)
        get_r(n+1, q) = -1;

    for (int q = 0; q <= k; q++)
    {
	    for (int p = -q; p <= n; p++)
	    {
            int R = max(
                get_r(p, q-1) + 1,
                max(
	                get_r(p-1, q-1),
	                get_r(p+1, q-1) + 1
                )
            );
            R = min(R, m);
            while (R < m && R + p < n && x[R] == y[R + p]) R++;
            get_r(p, q) = R;
            if (R == m) res.push_back(p + m);
	    }
    }

    cout << x << "\n" << y << "\n\n";
    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i] << "\n";
    }
}