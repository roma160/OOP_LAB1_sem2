#pragma once

#include <string>
#include <vector>
#include <set>
#include "deps/suffixtree.h"
#include "deps/lca.h"

using namespace std;

namespace string_algorithms
{
    /// <summary>
    /// O(nk) algorithm for searching x in y with k mistakes.
    /// </summary>
    /// <returns>
    /// Set of all indexes i, on which occurrence-substring of y is ending.
    /// </returns>
    set<int> task2_k_differences(const string& y, const string& x, int k)
    {
        auto tree = suffixtree::build(y + "#" + x + "$");
        auto _lca = lca(move(tree.reduced_nodes));

        int m = x.size();
        int n = y.size();

        vector<vector<int>> r(m + n + 3, vector<int>(k + 2));
        auto get_r = [&r, m](int p, int q) -> int&
        { return r[p + m + 1][q + 1]; };

        set<int> res;
        for (int p = 0; p <= n; p++)
            get_r(p, -1) = -1;

        for (int p = -k - 1; p <= -1; p++)
        {
            get_r(p, -p - 1) = -p - 1;
            get_r(p, -p - 2) = -p - 2;
        }

        for (int q = -1; q <= k; q++)
            get_r(n + 1, q) = -1;

        for (int q = 0; q <= k; q++)
        {
            for (int p = -q; p <= n; p++)
            {
                int R = max(
                    get_r(p, q - 1) + 1,
                    max(
                        get_r(p - 1, q - 1),
                        get_r(p + 1, q - 1) + 1
                    )
                );
                R = min(R, m);

                R += tree.node_to_length[
                    _lca.find(
                        tree.suffix_to_node[y.size() + 1 + R],
                        tree.suffix_to_node[R + p]
                    )
                ];

                while (R < m && R + p < n && x[R] == y[R + p]) R++;
                get_r(p, q) = R;
                if (R == m) res.insert(p + m);
            }
        }
        return res;
    }
}
