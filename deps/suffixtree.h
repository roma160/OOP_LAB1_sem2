#pragma once

#include <map>
#include <vector>
#include <string>
#include <sstream>

#define UNIQUE_CHAR_1 '$'
#define UNIQUE_CHAR_2 '#'

struct buff_tree;

namespace suffixtree
{
    using namespace std;
    struct node
    {
        int l, r;
        int parent;
        int linked_node;
        map<char, int> children;

        node(int l = 0, int r = 0, int parent = -1);

        int len();

        int& get(char c);
    };

    struct state
    {
        int node, pos;

        state(int node_id = 0, int pos = 0);
    };

    struct tree
    {

        vector<node> nodes;
        string str;

        state go(state st, int l, int r);
        int split(state st);
        int get_link(int node);

        tree(string _str);

        string get_substr(int start_pos, int end_pos);
        string log_tree();
        string log_node(int parent);
    };
} // namespace suffixtree
