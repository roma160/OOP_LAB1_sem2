#pragma once
#include <vector>
#include <map>
#include <string>

#define TERMINATING_CHARACTER '$'

using namespace std;

/// <summary>
/// The algorithm source:
///	https://github.com/adamserafini/suffix-tree
/// </summary>
class suffix_tree
{
private:
	struct node;
	struct suffix;

	string tree_string;
	string log_node(node* parent);
	string get_substr(int start_pos, int end_pos);

	enum Rule { RULE_2, RULE_3 };

	// SPA: Single Phase Algorithm (Gusfield, 1997)
	void SPA(int i);

	// SEA: Single Extension Algorithm (Gusfield, 1997)
	Rule SEA(suffix& previous_suffix, int j, int i);

	// The 'skip/count' trick for traversal (Gusfield, 1997)
	suffix get_suffix(node* origin, int begin_index, int end_index);

	// Apply Suffix Extension Rule 2 (Gusfield, 1997)
	void rule2(suffix& suffix, int char_index, int new_leaf_ID);

	node* root;
	int internal_node_ID;
	int length;
	int* current_end;
	node* last_leaf_extension;

public:
	struct node
	{
		node* parent;
		map<int, node*> children;
		node* suffix_link;

		int begin_index;
		int* end_index;

		/// <summary>
		/// The id for logging
		/// </summary>
		int id;

		node(node* parent, int begin_index, int* end_index, int id);

		/// <summary>
		/// The length of the substring from begin_index till end_index
		/// </summary>
		int get_edge_length() const;
		bool is_leaf() const;
		/// <summary>
		/// Gets child, that ends with a such char (which is specified by char index in main string)
		/// </summary>
		node* get_child(const suffix_tree& tree, int char_index) const;
		/// <summary>
		/// "Hashing" for storing children.
		///	(check the code for more info)
		/// </summary>
		static int get_key(const suffix_tree& tree, int index);

		// These algorithms are to be executed after the tree is updated.
		void add_child(const suffix_tree& tree, node* child);
		void remove_child(const suffix_tree& tree, node* child);
		void split_edge(const suffix_tree& tree, int char_index, int new_node_id);
	};

	struct suffix
	{
		node* n;
		bool new_internal_node;
		int char_index;

		suffix(node* n, int index);

		bool ends_at_node() const;
		bool ends_at_leaf() const;
		bool continues_with_char(const suffix_tree& tree, int tree_index) const;

		bool rule2_conditions(const suffix_tree& tree, int tree_index) const;
		node* walk_up(int& begin_index, int& end_index) const;
	};

	suffix_tree();

	void construct(string s);

	string log_tree();

	char get_char_at_index(int index) const;
};

