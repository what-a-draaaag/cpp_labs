#pragma once

#include "huffman_tree.h"
#include <fstream>
#include <cmath>

class file_writer{
public:
	file_writer(std::ofstream& out);

	std::ofstream& out;

	void write_table(huffman_tree::Table& table);
	void write_data(std::vector<char>& data, huffman_tree::Table& table);
};