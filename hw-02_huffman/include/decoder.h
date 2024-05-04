#pragma once

#include "huffman_tree.h"
#include <deque>


class decoder{
public:
	std::deque<bool> encoded_data;
	huffman_tree::Table table;

	decoder(std::deque<bool>& encoded_data, huffman_tree::Table& table);

	std::vector<char> decode_data();
};