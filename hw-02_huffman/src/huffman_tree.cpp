#include "huffman_tree.h"

bool comparator(huffman_node* first, huffman_node* second){
	return first->frequency > second->frequency;
}

void huffman_tree::build(std::vector<char> data){
	std::map<char, int> frequencies;
	for (char symbol : data){
		frequencies[symbol]++;
	}
	nodes.clear();
	for (auto symbol : frequencies){
		nodes.push_back(new huffman_node(symbol.first, symbol.second, nullptr, nullptr));
	}
	std::sort(nodes.begin(), nodes.end(), comparator);
	while (nodes.size() >1){
		//huffman_node* left = nodes.back();
		nodes.pop_back();
		//huffman_node* right = nodes.back();
		nodes.pop_back();
	}
	root = nodes.back();
}

int huffman_tree::get_size(){
	return nodes.size();
}

std::vector<char> huffman_tree::make_table(){
	std::vector<char> empty;
	return empty;
}