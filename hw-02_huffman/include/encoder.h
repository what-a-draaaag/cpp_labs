#pragma once

#include "huffman_tree.h"
#include "huffman_compressor.h"
#include "file_writer.h"

class encoder{
public:
	std::vector<char> data;
	huffman_tree::Table table;

	encoder(std::vector<char>& data, huffman_tree::Table& table);

	std::vector<bool> encode_data();
};