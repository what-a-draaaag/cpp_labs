#include "huffman_tree.h"

const int bits_in_byte = 8;


huffman_tree::huffman_tree(std::map<char, unsigned int> frequancies){
	std::set<std::pair<std::vector<char>, unsigned int>> tree;
	for (auto symbol : frequancies){
		std::vector<char> ch{symbol.first};
		tree.insert(std::make_pair(ch, symbol.second));
	}
	while (tree.size()>1){
		std::pair<std::vector<char>, unsigned int> first = *tree.begin();
		tree.erase(first);
		std::pair<std::vector<char>, unsigned int> second = *tree.begin();
		tree.erase(second);
		for (auto ch : first.first){
			table.code_vectors[ch].push_back(0);
		}
		for (auto ch : second.first){
			table.code_vectors[ch].push_back(1);
		}
		std::vector<char> new_elem = first.first;
		new_elem.insert(new_elem.end(), second.first.begin(), second.first.end());
		tree.insert(std::make_pair(new_elem, first.second+second.second));
	}

	for (auto pair: tree){
		std::reverse(pair.first.begin(), pair.first.end());
	}
}


std::string huffman_tree::Table::get_code(char ch){
	return codes[ch];
}

void huffman_tree::Table::make_codes(){
	for (auto ch : code_vectors){
		std::reverse(ch.second.begin(), ch.second.end());
		std::string code = "";
		for (unsigned int i=0; i<ch.second.size(); i++){
			code.push_back(ch.second[i]);
		}
		codes[ch.first] = code;
	}
}

int huffman_tree::Table::get_code_len(char ch){
	return codes[ch].size();
}

int huffman_tree::Table::size(){
	return bits.size();
}


bool get_bit_from_byte(char byte, int index){
	return (byte >> index) & 1;
}

std::vector<bool> huffman_tree::Table::to_bits(){
	std::vector<bool> bits_in_vector;
	for (auto ch : code_vectors){
		for (int i = 0; i<bits_in_byte; i++){
			bits_in_vector.push_back(get_bit_from_byte(ch.first, i));
		}
		uint8_t code_size = ch.second.size();
		for (int i = 0; i<bits_in_byte; i++){
			bits_in_vector.push_back(get_bit_from_byte(code_size, i));
		}
		for (int i = 0; i<code_size; i++){
			bits_in_vector.push_back(ch.second[i]);
		}
	}
	bits = bits_in_vector;
	return bits_in_vector;
}

void huffman_tree::print_statistics(){
	std::for_each(statistics.begin(), statistics.end(), [](int i){std::cout << i << std::endl;});
}