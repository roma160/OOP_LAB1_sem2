#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "task2_deps/suffixtree.h"
#include "task2_deps/lca.h"

using namespace std;

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%9B%D0%B0%D0%BD%D0%B4%D0%B0%D1%83-%D0%92%D0%B8%D1%88%D0%BA%D0%B8%D0%BD%D0%B0_(k_%D1%80%D0%B0%D0%B7%D0%BB%D0%B8%D1%87%D0%B8%D0%B9)

int main()
{
    string x("father");
    string y(R"(In entirely be to at settling felicity. Fruit two match men you seven share. Needed as or is enough points. Miles at smart ﻿no marry whole linen mr. Income joy nor can wisdom summer. Extremely depending he gentleman improving intention rapturous as.

        Bed sincerity yet therefore forfeited his certainty neglected questions.Pursuit chamber as elderly amongst on.Distant however warrant farther to of.My justice wishing prudent waiting in be.Comparison age not pianoforte increasing delightful now.Insipidity sufficient dispatched any reasonably led ask.Announcing if attachment resolution sentiments admiration me on diminution.)");

    // aceabpcqdeabcr#abcde
    auto tree = suffixtree::build(y + "#" + x + "$");
    auto _lca = lca(move(tree.reduced_nodes));

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

            int x_pos = tree.suffix_to_node[y.size() + 1 + R];
            int y_pos = tree.suffix_to_node[R + p];
            R += tree.node_to_length[_lca.find(x_pos, y_pos)];

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