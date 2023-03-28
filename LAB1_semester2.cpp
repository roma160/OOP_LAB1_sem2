#include <iomanip>
#include <vector>
#include <iostream>

#include "task2/lca.h"
#include "task2/rmq.h"

using namespace std;

int main()
{
    vector<vector<int>> tree = {
        {1}, {4, 2}, {3}, {}, {5, 6}, {}, {}
    };

    lca lca(tree);
    while (true) {
        int l, r;
        cin >> l >> r;
        int f = lca.find(l - 1, r - 1) + 1;
        cout << l << " " << r << ") " << f << "\n";
    }
}