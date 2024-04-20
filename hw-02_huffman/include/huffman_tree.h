#pragma once
#include "huffman_node.h"
#include <istream>
#include <vector>
#include <map>
#include <algorithm>



class huffman_tree{
public:
	std::vector<huffman_node*> nodes;
	huffman_node* root;
	int get_size();
	
	void build(std::vector<char> data);
};