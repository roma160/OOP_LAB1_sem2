#pragma once

#include <map>
#include <vector>
#include <string>
#include <sstream>

struct buff_tree;

namespace suffixtree
{
    struct node {
        int len;
        std::map<char, int> children;
    };

    struct tree {
        std::vector<node> char_nodes;
        std::vector<std::vector<int>> reduced_nodes;

        tree(buff_tree* buff);
    };

    tree build(std::string s);
} // namespace suffixtree
