#pragma once

#include "huffman_tree.h"

class encoder{
public:
	encoder(std::vector<char>& data, huffman_tree::Table& table);

	std::vector<bool> encode_data();
	
private:
	std::vector<char> data;
	huffman_tree::Table table;
};