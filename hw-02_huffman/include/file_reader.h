#pragma once

#include "huffman_tree.h"
#include <fstream>
#include <vector>
#include <map>


class file_reader{
public:
	std::ifstream& in;

	file_reader(std::ifstream& in);

	bool is_compressed();
	void read_file_compress(std::vector<char>& data, std::map<char, unsigned int>& frequencies);
	void read_file_decompress(huffman_tree& ht, std::vector<char>& data);
};