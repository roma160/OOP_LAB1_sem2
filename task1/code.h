#pragma once

#include <string>
#include <vector>

#include "deps/input.h"

using namespace std;

namespace string_algorithms
{
    // Morris–Pratt algorithm
    int task1(const string& s, const string& x)
    {
        int x_size = x.size();
        int s_size = s.size();

        // Precomputing value of borders length
        vector<int> b_length(x_size + 1);
        b_length[0] = -1;

        int j = -1;
        for (int i = 0; i < x_size;)
        {
            while (j > -1 && x[i] != x[j])
                j = b_length[j];
            i++; j++;
            if (x[i] == x[j]) b_length[i] = b_length[j];
            else b_length[i] = j;
        }

        // Starting the search
        j = 0;
        for (int i = 0; i < s_size;)
        {
            while (j > -1 && s[i] != x[j])
                j = b_length[j];
            i++; j++;
            if (j >= x_size)
                return i - j;
        }
        return -1;
    }

    void test_task1()
    {
        string s = read_string("s");
        string x = read_string("x");
        cout << "Index of occurrence (0-indexed) : " << task1(s, x);
    }
}
