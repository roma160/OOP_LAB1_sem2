#include "lca.h"
#include <queue>

void lca::dfs(int node, int depth, const vector<vector<int>>& tree, int& i, vector<int>& d)
{
    d[i] = depth;
    vtx[i] = node;
    I[node] = i;
    i++;

    for (int j = 0; j < tree[node].size(); j++) {
        dfs(tree[node][j], depth + 1, tree, i, d);

        d[i] = depth;
        vtx[i] = node;
        i++;
    }
}

lca::lca(vector<vector<int>> tree, int root) :
    N(tree.size()), I(N), vtx(2 * N - 1)
{
    int i = 0;
    vector<int> depth_list(2 * N - 1);
    dfs(root, 0, tree, i, depth_list);

    d = rmq(depth_list);
}

int lca::find(int a, int b) const {
    a = I[a];
    b = I[b];
    if (a > b) swap(a, b);
    int i = d.min(a, b).index;
    return vtx[i];
}
