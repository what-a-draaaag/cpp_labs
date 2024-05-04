#include "huffman_tree.h"

const int bits_in_byte = 8;


huffman_tree::huffman_tree(std::map<char, unsigned int> frequancies){
	std::set<std::pair<unsigned int, std::vector<char>>> tree;
	for (auto symbol : frequancies){
		std::vector<char> ch{symbol.first};
		tree.insert(std::make_pair(symbol.second, ch));
	}
	if (tree.size() == 1){
		std::pair<unsigned int, std::vector<char>> elem = *tree.begin();
		tree.erase(elem);
		for (auto ch : elem.second){
			table.code_vectors[ch].insert(table.code_vectors[ch].begin(), 0);
		}
	}
	while (tree.size()>1){
		std::pair<unsigned int, std::vector<char>> elem1 = *tree.begin();
		tree.erase(elem1);
		std::pair<unsigned int, std::vector<char>> elem2 = *tree.begin();
		tree.erase(elem2);
		for (auto ch : elem1.second){
			table.code_vectors[ch].insert(table.code_vectors[ch].begin(), 0);
		}
		for (auto ch : elem2.second){
			table.code_vectors[ch].insert(table.code_vectors[ch].begin(), 1);
		}
		std::vector<char> new_elem = elem1.second;
		new_elem.insert(new_elem.end(), elem2.second.begin(), elem2.second.end());
		tree.insert(std::make_pair(elem1.first+elem2.first, new_elem));
	}
	table.to_bits();
	table.make_codes();
}


std::string huffman_tree::Table::get_code(char ch){
	return char_to_code[ch];
}

void huffman_tree::Table::make_codes(){
	for (auto ch : code_vectors){
		std::string code = "";
		for (unsigned int i=0; i<ch.second.size(); i++){
			code.push_back(ch.second[i]);
		}
		char_to_code[ch.first] = code;
	}
}

int huffman_tree::Table::get_code_len(char ch){
	return char_to_code[ch].size();
}

int huffman_tree::Table::size(){
	return bits.size();
}


bool get_bit_from_byte(char byte, int index){
	return (byte >> (bits_in_byte - index - 1)) & 1;
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