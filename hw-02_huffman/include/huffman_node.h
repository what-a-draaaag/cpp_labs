#pragma once

class huffman_node{
public:
	char value = '\0';
	int frequency = 0;
	bool is_leaf = true;
	huffman_node* left;
	huffman_node* right;

	huffman_node() = default;
	huffman_node(char value, int frequency, huffman_node* left, huffman_node* right);
};