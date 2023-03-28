#pragma once

#include <map>
#include <vector>
#include <string>
#include <sstream>

struct buff_tree;

namespace suffixtree
{
    struct tree {
        std::vector<int> suffix_to_node;
        std::vector<int> node_to_length;
        std::vector<std::vector<int>> reduced_nodes;

        tree(buff_tree* buff);
    };

    tree build(std::string s);
} // namespace suffixtree
