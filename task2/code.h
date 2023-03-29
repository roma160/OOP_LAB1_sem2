#pragma once

#include <string>
#include <vector>
#include <set>

#include "deps/suffixtree.h"
#include "deps/lca.h"
#include "deps/input.h"

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
        // Precomputing stage
        string to_precompute = y + UNIQUE_CHAR_2 + x + UNIQUE_CHAR_1;
        suffixtree::tree buff(to_precompute);
        vector<suffixtree::node>& nodes = buff.nodes;

        vector<int> suffix_to_node(to_precompute.size());
        vector<int> node_to_length(nodes.size());
        vector<vector<int>> reduced_nodes(nodes.size());

        for (int i = 0; i < nodes.size(); i++)
        {
            // Reduced node
            for (auto it = nodes[i].children.begin(); it != nodes[i].children.end(); it++)
                reduced_nodes[i].push_back(it->second);

            // Node to length
            node_to_length[i] = nodes[i].len();
        }

        for (int i = 0; i < to_precompute.size(); i++)
        {
            int cur_node = 0;
            int j = i;
            for (; j < to_precompute.size();)
            {
                cur_node = nodes[cur_node].get(to_precompute[j]);
                j += node_to_length[cur_node];
            }
            suffix_to_node[i] = cur_node;
        }
        auto _lca = lca(move(reduced_nodes));

        // Algorithm start
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

                R += node_to_length[
                    _lca.find(
                        suffix_to_node[y.size() + 1 + R],
                        suffix_to_node[R + p]
                    )
                ];

                while (R < m && R + p < n && x[R] == y[R + p]) R++;
                get_r(p, q) = R;
                if (R == m) res.insert(p + m);
            }
        }
        return res;
    }

    void test_task2()
    {
        string y = read_string("y");
        string x = read_string("x");
        int k = read_int("k");

        auto res = task2_k_differences(y, x, k);
        cout << "Answer: " << sequence_to_string(vector<int>(res.begin(), res.end()));
    }
}
