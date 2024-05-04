#pragma once

#include "huffman_tree.h"
#include "encoder.h"
#include <fstream>
#include <iostream>
#include <cmath>

class file_writer{
public:
	file_writer(std::ofstream& out);

	bool is_useful(huffman_tree& ht, huffman_tree::Table& table,  std::vector<char>& data) const;
	void write_table(huffman_tree& ht, huffman_tree::Table& table) const;
	void write_data_compress(huffman_tree& ht, std::vector<char>& data, huffman_tree::Table& table) const;
	void write_data_decompress(std::vector<char>& data) const;
private:
	void write_vector(std::vector<bool>& v) const;
	std::ofstream& out;

	uint8_t get_byte(std::vector<bool>& bits, unsigned int index) const;
};