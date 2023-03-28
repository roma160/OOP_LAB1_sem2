#pragma once
#include <string>
#include <vector>
#include <queue>

using namespace std;

namespace string_algorithms
{
	string task6_optimal(const string& s)
	{
        // Precomputing stage
        suffixtree::tree buff(s + UNIQUE_CHAR_1);
        vector<suffixtree::node>& nodes = buff.nodes;

        // Actual computing
        string max_s = "";

        queue<pair<int, string>> q;
        q.push({ 0, "" });
        while (!q.empty())
        {
            auto f = q.front();
            q.pop();
            int node = f.first;
            string node_str = f.second;
            bool is_inner = false;
            for (auto it : nodes[node].children)
            {
                if (it.second == -1) continue;
                is_inner = true;
                suffixtree::node& cur = nodes[it.second];
                q.push({ it.second, node_str + s.substr(cur.l, cur.r - cur.l) });
            }

            if (is_inner && node_str.size() > max_s.size())
                max_s = node_str;
        }

		return max_s;
	}
}