#pragma once
#include "huffman_node.h"
#include <istream>
#include <vector>
#include <map>
#include <algorithm>



class huffman_tree{
public:
	std::vector<huffman_node*> nodes;
	huffman_node* root = nullptr;
	int get_size();
	std::vector<char> make_table(); //FIXIT!!!!!!
	
	void build(std::vector<char> data);
};