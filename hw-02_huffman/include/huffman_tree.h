#pragma once
#include <istream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>




class huffman_tree{
public:
	std::map<char, std::vector<bool>> table;

	huffman_tree(std::map<char, unsigned int> frequancies);

};