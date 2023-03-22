#include "suffix_tree.h"

#include <sstream>
#include <streambuf>

/*
 * THE NODE STRUCT IMPLEMENTATION
 */

suffix_tree::node::node(node* parent, int begin_index, int* end_index, int id)
{
	this->parent = parent;
	this->begin_index = begin_index;
	this->end_index = end_index;
	this->id = id;
	suffix_link = nullptr;
}

int suffix_tree::node::get_edge_length() const
{ return *end_index - begin_index + 1; }

bool suffix_tree::node::is_leaf() const
{ return children.empty(); }

suffix_tree::node* suffix_tree::node::get_child(const suffix_tree& tree, int char_index) const
{
	int key = get_key(tree, char_index);
	map<int, node*>::const_iterator i = children.find(key);
	if (i != children.end()) return i->second;
	return nullptr;
}

int suffix_tree::node::get_key(const suffix_tree& tree, int index)
{
	char c = tree.get_char_at_index(index);
	if (c != TERMINATING_CHARACTER) return -c;
	return index;
}

void suffix_tree::node::add_child(const suffix_tree& tree, node* child)
{
	int key = get_key(tree, child->begin_index);
	children[key] = child;
}

void suffix_tree::node::remove_child(const suffix_tree& tree, node* child)
{
	int key = get_key(tree, child->begin_index);
	children.erase(key);
}

void suffix_tree::node::split_edge(const suffix_tree& tree, int char_index, int new_node_id)
{
	node* new_node = new node(
		parent, begin_index, new int(char_index), new_node_id);

	// Replacing this with new_node
	parent->remove_child(tree, this);
	parent->add_child(tree, new_node);

	// Connecting this to a new_node
	this->parent = new_node;
	this->begin_index = char_index + 1;
	new_node->add_child(tree, this);
}



/*
 * THE SUFFIX STRUCT IMPLEMENTATION
 */
suffix_tree::suffix::suffix(node* n, int index)
{
	this->n = n;
	this->char_index = index;
	new_internal_node = false;
}

bool suffix_tree::suffix::ends_at_node() const
{ return char_index == *n->end_index; }

bool suffix_tree::suffix::ends_at_leaf() const
{ return ends_at_node() && n->is_leaf(); }

bool suffix_tree::suffix::continues_with_char(const suffix_tree& tree, int tree_index) const
{
	char c = tree.get_char_at_index(tree_index);
	bool is_terminal(c == TERMINATING_CHARACTER);
	return (ends_at_node() && n->get_child(tree, tree_index) != nullptr) ||
		(!ends_at_node() && tree.get_char_at_index(char_index + 1) == c &&
			(!is_terminal || char_index + 1 == tree_index));
}

bool suffix_tree::suffix::rule2_conditions(const suffix_tree& tree, int tree_index) const
{ return !ends_at_leaf() && !continues_with_char(tree, tree_index); }

suffix_tree::node* suffix_tree::suffix::walk_up(int& begin_index, int& end_index) const
{
	if (ends_at_node() && n->suffix_link != nullptr) {
		begin_index = *n->end_index;
		end_index = *n->end_index - 1;
		return n;
	}

	begin_index = n->begin_index;
	end_index = char_index;
	return n->parent;
}



/*
 * THE SUFFIX TREE STRUCT IMPLEMENTATION
 */

suffix_tree::suffix_tree()
{
	// Internal node IDs start at zero and decrement. For example, the root node,
	// which can be considered the first internal node has an ID of 0. The next
	// internal node has an ID of -1, followed by -2 and so forth.

	// While not neccessary for the algorithm to function, each node having a
	// unique ID is important when using Graphiz to visualize the structure.
	internal_node_ID = 0;

	current_end = new int(0);
	root = new node(nullptr, 1, current_end, internal_node_ID);
}

void suffix_tree::construct(string s)
{
	length = s.size();
	tree_string = s;

	// Construct Implicit Tree I(1).
	(*current_end)++;
	last_leaf_extension = new node(root, 1, current_end, 1);
	root->add_child(*this, last_leaf_extension);

	for (int i = 1; i < length; i++) {
		SPA(i);
	}
}

char suffix_tree::get_char_at_index(int index) const
{
	return tree_string[index - 1];
}

string suffix_tree::log_node(node* parent)
{
	std::map<int, node*>::iterator it = parent->children.begin();

	std::stringstream buffer;

	// Internal nodes (nodes with ID <= 0) are unlabelled points, leaves
	// (nodes with ID > 0) show the ID as plaintext.
	buffer << parent->id << "[shape="
		<< ((parent->id <= 0) ? "point" : "plaintext") << "];\n";

	for (; it != parent->children.end(); it++) {
		// Child nodes are stored on the parent node in a map of integers
		// (it->first) to Node pointers (it->second).
		node* child_node = it->second;
		buffer << parent->id << "->" << child_node->id << " [label = \""
			<< get_substr(child_node->begin_index, *(child_node->end_index))
			<< "\"];\n" << log_node(child_node);
	}

	// Print the suffx link, if there is one.
	node* suffix_link = parent->suffix_link;
	if (suffix_link)
		buffer << "\"" << parent->id << "\" -> " << "\""
		<< suffix_link->id << "\" [style=dashed arrowhead=otriangle];\n";

	return buffer.str();
}

string suffix_tree::get_substr(int start_pos, int end_pos)
{
	if (start_pos > end_pos) return std::string();
	// This is 1-indexed to match the algorithm's original description in the
	// paper. For example, "foobar".get_substr(2, 4) == "oob".
	return tree_string.substr(start_pos - 1, end_pos - start_pos + 1);
}

void suffix_tree::SPA(int i)
{
	// Do phase i + 1.

	suffix previous_suffix(last_leaf_extension, *current_end);

	// Increment the current_end pointer: this implicitly applies Rule 1 to all
	// leaf edges in the tree.
	(*current_end)++;

	// Explicitly compute successive extensions starting at j(i) + 1 where (i)
	// is the ID of the last leaf extension from the previous phase.
	for (int j = (last_leaf_extension->id + 1); j <= i + 1; j++) {
		Rule rule_applied = SEA(previous_suffix, j, i);
		if (rule_applied == RULE_3)
			break;
	}
}

suffix_tree::Rule suffix_tree::SEA(suffix& previous_suffix, int j, int i)
{
	int begin_index, end_index;
	node* origin = previous_suffix.walk_up(begin_index, end_index);
	suffix suffix = (origin == root ? get_suffix(root, j, i)
		: get_suffix(origin->suffix_link, begin_index, end_index));

	Rule rule_applied;
	if (suffix.rule2_conditions(*this, i + 1)) {
		rule2(suffix, i + 1, j);
		rule_applied = RULE_2;
	}
	else {
		rule_applied = RULE_3;
	}

	if (previous_suffix.new_internal_node)
		previous_suffix.n->suffix_link = suffix.n;

	previous_suffix = suffix;
	return rule_applied;
}

suffix_tree::suffix suffix_tree::get_suffix(node* origin, int begin_index, int end_index)
{
	int char_index = *origin->end_index;

	while (begin_index <= end_index) {
		origin = origin->get_child(*this, begin_index);
		if (origin->get_edge_length() < end_index - begin_index + 1)
			char_index = *origin->end_index;
		else
			char_index = origin->begin_index + (end_index - begin_index);
		begin_index += origin->get_edge_length();
	}
	return suffix(origin, char_index);
}

void suffix_tree::rule2(suffix& suffix, int char_index, int new_leaf_ID)
{
	if (!suffix.ends_at_node()) {  // eg. in case 2 (path ends inside an edge)
		suffix.n->split_edge(*this, suffix.char_index, --internal_node_ID);
		suffix.n = suffix.n->parent;
		suffix.new_internal_node = true;
	}
	node* new_leaf = new node(suffix.n, char_index, current_end, new_leaf_ID);
	suffix.n->add_child(*this, new_leaf);
	last_leaf_extension = new_leaf;
}

string suffix_tree::log_tree()
{
	return "digraph g{\n" + log_node(root) + "}";
}