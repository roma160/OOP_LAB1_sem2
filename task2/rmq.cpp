#include "rmq.h"

#include <algorithm>

int log(int n) {
    int ret = 0;
    while (n >>= 1) ret++;
    return ret;
}

rmq::rmq() : N(-1), log_n(0), block_size(0), K(0) {}

rmq::rmq(vector<int> A) :
    N(A.size()), log_n(log(N)), block_size(log_n / 2),
    K(N / block_size + (N % block_size > 0)),

    A(A), B(K, -1), ST(K, vector<int>(log_n + 1)), type(K, 0),
    block_min(K, vector<vector<int>>(block_size, vector<int>(block_size, -1)))
{
    // предподсчитаем позиции минимумов в каждом блоке
    for (int i = 0; i < N; i++) {
        int cur_block = i / block_size;
        if (B[cur_block] == -1 || A[B[cur_block]] > A[i])
            B[cur_block] = i;
    }

    // построим Sparse table на массиве B
    for (int i = 0; i < K; i++)
        ST[i][0] = B[i];
    for (int j = 1; j <= log_n; j++)
        for (int i = 0; i < K; i++) {
            int ind = (1 << (j - 1)) + i;
            if (ind >= K)
                ST[i][j] = ST[i][j - 1];
            else if (A[ST[i][j - 1]] > A[ST[ind][j - 1]])
                ST[i][j] = ST[ind][j - 1];
            else
                ST[i][j] = ST[i][j - 1];
        }

    // Посчитаем тип для каждого блока
    for (int i = 0; i < K * block_size; i++) {
        int offset = i % block_size;
        if (offset > 0 && (i >= N || A[i - 1] < A[i]))
            type[i / block_size] += (1 << (offset - 1));
    }

    // Осталось только для каждого блока предподсчитать позиции минимумов на всех подотрезках
    for (int i = 0; i < K; i++) {
        int t = type[i];
        if (block_min[t][0][0] != -1)
            continue;
        for (int l = 0; l < block_size; l++) {
            block_min[t][l][l] = l;
            for (int r = l + 1; r < block_size; r++) {
                block_min[t][l][r] = block_min[t][l][r - 1];
                if ((i * block_size + r <= N) && (A[i * block_size + block_min[t][l][r]] > A[i * block_size + r]))
                    block_min[t][l][r] = r;
            }
        }
    }
}

int rmq::block_rmq(int block_number, int l, int r) const {
    return block_min[type[block_number]][l][r] + block_number * block_size;
}

rmq::minval::operator int() const { return val; }
rmq::minval::minval() : val(-1), index(-1) {}
rmq::minval::minval(int v, int i) : val(v), index(i) {}
rmq::minval::minval(int i, const rmq* q) : index(i), val(q->A[i]) {}
rmq::minval rmq::minval::min(minval a, minval b) { return a <= b ? a : b; }

rmq::minval rmq::min(int l, int r) const {
    int bl = l / block_size;
    int br = r / block_size;
    if (bl == br) // если оба индекса внутри одного блока
        return minval(block_rmq(bl, l % block_size, r % block_size), this);

    minval left(block_rmq(bl, l % block_size, block_size - 1), this); // найдем минимум на отрезке от l до конца блока, содержащего l
    minval right(block_rmq(br, 0, r % block_size), this);              // найдем минимум от начала блока, содержащего r, до r
    minval sides = minval::min(left, right);
    if (bl + 1 >= br) return sides;

    // найдем минимум на блоках между крайними
    int power = log(br - bl - 1);
    minval insides = minval::min(
        { ST[bl + 1][power], this },
        { ST[br - (1 << power)][power], this }
    );
    return minval::min(insides, sides);
}