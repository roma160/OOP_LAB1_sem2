#include "suffixtree.h"

using namespace std;

suffixtree::node::node(int l, int r, int parent):
	l(l), r(r), parent(parent), linked_node(-1) {}

int suffixtree::node::len()
{ return r - l; }

int& suffixtree::node::get(char c)
{
	if (!children.count(c))
		children[c] = -1;
	return children[c];
}

suffixtree::state::state(int node_id, int pos):
	node(node_id), pos(pos) {}



// THE ALGORITHM

// We need to find str[l; r) after st
suffixtree::state suffixtree::tree::go(state st, int l, int r)
{
	// We will increse l (so the s[l; r) gets shorter)
	while (l < r)
		// If we run out of chars on cur node
		if (st.pos == nodes[st.node].len())
		{
			st = state(nodes[st.node].get(str[l]), 0);
			// No next node <=> didn't find the s[l; r)
			if (st.node == -1) return st;
		}
			// Still on the same node
		else
		{
			// If the node's char is different from ours => stop
			if (str[nodes[st.node].l + st.pos] != str[l])
				return state(-1, -1);

			// We are doing insertions by 1 char,
			//  so if we are here => we have found the place
			if (r - l < nodes[st.node].len() - st.pos)
				return state(st.node, st.pos + r - l);
			// In another case we jump to the end of the node
			l += nodes[st.node].len() - st.pos;
			st.pos = nodes[st.node].len();
		}
	return st;
}

// Doing the split at st
int suffixtree::tree::split(state st)
{
	// If resulting node is zero => do nothing
	if (st.pos == nodes[st.node].len())
		return st.node;
	// Same here, but jump to a different node
	if (st.pos == 0)
		return nodes[st.node].parent;

	// We are here, so we need to do an actual split
	node* cur_node = &nodes[st.node];
	// Creating the new node (contains LEFT part of split)
	nodes.push_back(node(cur_node->l, cur_node->l + st.pos, cur_node->parent));
	cur_node = &nodes[st.node]; // recovering the link

	int new_node_id = nodes.size() - 1;
	// Connecting nodes
	//  parent -> new_node
	nodes[cur_node->parent].get(str[cur_node->l]) = new_node_id;
	//            new_node -> old_node
	nodes[new_node_id].get(str[cur_node->l + st.pos]) = st.node;

	// Modifying the current node
	cur_node->parent = new_node_id;
	cur_node->l += st.pos;

	// Return id of the new node (the middle one)
	return new_node_id;
}

// Recursively finds the link for the node v
int suffixtree::tree::get_link(int node)
{
	// The simplest case
	if (nodes[node].linked_node != -1)
		return nodes[node].linked_node;
	if (nodes[node].parent == -1) // According to rule 3, we should do nothing
		return 0;

	// In other case, recursively search link on parents
	int parent_linked_node = get_link(nodes[node].parent);
	// Now we compute the link for this particular case
	nodes[node].linked_node = split(
		// we do search
		go(
			// from parent's link
			state(
				parent_linked_node,
				nodes[parent_linked_node].len()
			),
			// to current node's s[l, r)
			nodes[node].l + (nodes[node].parent == 0),
			nodes[node].r
		)
		// after we've found the place, we try to connect to it
	);
	return nodes[node].linked_node;
}

suffixtree::tree::tree(string _str): str(_str)
{
	state current_state;
	nodes = vector<node>{ node() };
	int n = str.size();
	for (int l = 0; l < n; l++) {
		while (true)
		{
			// Try to locate new char
			state new_state = go(current_state, l, l + 1);
			// If it is present <=> tree's extended
			if (new_state.node != -1)
			{
				current_state = new_state;
				break;
			}

			int middle_node_id = split(current_state); // id of new node (located in the middle)

			// Adding new leaf for the current suffix
			int new_node_id = nodes.size();
			//     (we use n here, as we're adding the leaf node, and it would remain as a leaf)
			nodes.push_back(node(l, n, middle_node_id));
			//      middle -> new_node
			nodes[middle_node_id].get(str[l]) = new_node_id;

			// Using Rule 3
			//  After an insert from the active node which is not the root node,
			//  we must follow the suffix link and set the active node to the node
			//  it points to. If there is no a suffix link, set the active node to
			//  the root node. Either way, active edge and active length stay unchanged.
			current_state.node = get_link(middle_node_id);
			current_state.pos = nodes[current_state.node].len();

			// If we are at root => stop
			if (middle_node_id == 0) break;
		}
	}
}

string suffixtree::tree::get_substr(int start_pos, int end_pos)
{
	if (start_pos > end_pos) return std::string();
	return str.substr(start_pos, end_pos - start_pos);
}

string suffixtree::tree::log_tree()
{
	return "digraph g{\n" + log_node(0) + "}";
}

string suffixtree::tree::log_node(int parent)
{
	map<char, int>::iterator it = nodes[parent].children.begin();

	stringstream buffer;

	buffer << parent << "[shape="
		<< ((parent <= 0) ? "point" : "circle") << "];\n";

	for (; it != nodes[parent].children.end(); it++)
	{
		// Child nodes are stored on the parent node in a map of integers
		// (it->first) to Node pointers (it->second).
		int child_node_id = it->second;
		node* child_node = &nodes[child_node_id];
		buffer << parent << "->" << child_node_id << " [label = \""
			<< get_substr(child_node->l, child_node->r)
			<< "\"];\n"
			<< log_node(child_node_id);
	}

	// Print the suffx link, if there is one.
	int suffix_link_id = nodes[parent].linked_node;
	if (suffix_link_id != -1)
		buffer << "\"" << parent << "\" -> "
			<< "\""
			<< suffix_link_id << "\" [style=dashed arrowhead=otriangle];\n";

	return buffer.str();
}