#include <iomanip>
#include <vector>
#include <iostream>
#include <string>

#include "strings_algorithms.h"

using namespace std;

int main()
{
    cout << string_algorithms::task8(
        { 3, 4, 8, 4, 0, 9, 1, 2, 8, 3, 0, 2, 1 }, 8);
}