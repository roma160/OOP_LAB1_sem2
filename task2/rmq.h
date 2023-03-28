#pragma once

#include <vector>

using namespace std;

// https://neerc.ifmo.ru/wiki/index.php?title=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC_%D0%A4%D0%B0%D1%80%D0%B0%D0%BA%D0%B0-%D0%9A%D0%BE%D0%BB%D1%82%D0%BE%D0%BD%D0%B0_%D0%B8_%D0%91%D0%B5%D0%BD%D0%B4%D0%B5%D1%80%D0%B0
class rmq {
public:
    struct minval
    {
        int val, index;

        minval();
        minval(int v, int i);
        minval(int i, const rmq* q);

        operator int() const;

        static minval min(minval a, minval b);
    };

private:
    friend struct minval;

    int N, log_n, block_size, K;

    vector<int> A;
    vector<int> B;
    vector<vector<int>> ST;
    vector<int> type;
    vector<vector<vector<int>>> block_min;

    int block_rmq(int block_number, int l, int r) const;

public:
    rmq();
    rmq(vector<int> A);

    minval min(int l, int r) const;
};
