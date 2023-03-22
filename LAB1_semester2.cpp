#include <iostream>
#include "strings_algorithms.h"
#include "suffix_tree.h"

using namespace std;

int main()
{
    suffix_tree tree;
    tree.construct("abcabxabcd$");
    cout << tree.log_tree();
}