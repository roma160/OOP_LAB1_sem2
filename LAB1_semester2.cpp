#include <iomanip>
#include <vector>
#include <iostream>

#include "task2/rmq.h"

using namespace std;

int main()
{
    vector<int> A{ 1, 2, 1, 0, -1, -2, -1, 0, 1, 2, 3, 4, 5 };
    rmq q(A);

    int padding = 3;
    for (int i = 0; i < A.size(); i++) {
        cout << setw(padding) << i;
    }
    cout << "\n";

    for (int i = 0; i < A.size(); i++)
    {
        cout << setw(padding) << A[i];
    }
    cout << "\n";

    while (true) {
        int l, r;
        cin >> l >> r;
        cout << l << " " << r << ") " << q.min(l, r) << "\n";
    }
}