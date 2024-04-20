#include "huffman_tree.h"

huffman_node::huffman_node(char value, int frequency, huffman_node* left, huffman_node* right):
value(value), frequency(frequency), left(left), right(right) {}
