#pragma once

#include "huffman_tree.h"
#include "decoder.h"
#include <fstream>
#include <vector>
#include <map>


class file_reader{
public:
	bool file_is_compressed = false;

	file_reader(std::ifstream& in);

	void compressed_or_not_check();
	void read_file_compress(std::vector<char>& data, std::map<char, unsigned int>& frequencies);
	void read_file_decompress(huffman_tree& ht, std::vector<char>& data);
private:
	std::ifstream& in;	
	unsigned int table_size_in_bytes;
	unsigned int data_size_in_bytes;
	unsigned int data_size_in_bits;

	void read_table(huffman_tree& ht) const;
	std::vector<char> read_data() const;
	std::vector<char> read_not_compressed_data() const;

	std::deque<bool> bytes_to_bits(std::vector<char>& bytes) const;
	uint8_t get_first_byte(std::deque<bool>& bits) const;
};