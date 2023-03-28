#pragma once

#include <vector>

#include "rmq.h"

using namespace std;

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%A1%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B8_LCA_%D0%BA_%D0%B7%D0%B0%D0%B4%D0%B0%D1%87%D0%B5_RMQ#.D0.90.D0.BB.D0.B3.D0.BE.D1.80.D0.B8.D1.82.D0.BC
class lca {
private:
    const int N;
    vector<int> vtx;
    vector<int> I;
    rmq d;

    void dfs(int node, int depth, const vector<vector<int>>& tree, int& i, vector<int>& d);

public:
    lca(vector<vector<int>> tree, int root = 0);

    int find(int a, int b) const;
};
