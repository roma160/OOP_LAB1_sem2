#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "strings_algorithms.h"

using namespace std;

int main()
{
    cout << string_algorithms::task8(
        { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 8, 8, 9 }, 4)<<"\n";

    cout << string_algorithms::task9(
        { 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 8, 8, 9 }, 1);
}