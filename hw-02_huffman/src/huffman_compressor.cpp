#include "huffman_compressor.h"
#include "huffman_tree.h"
#include <fstream>

const int bits_in_byte = 8;

bool get_bit_from_byte(char byte, int index){
	return (byte >> index) & 1;
}

void read_data(std::ifstream& in, std::vector<char>& data, std::map<char, unsigned int>& frequancies){
	char c;
	while (in.get(c)){
		data.push_back(c);
		frequancies[c]++;
	}
}

void huffman_compressor::compress(std::ifstream& in, std::ofstream& out){
	std::vector<char> data;
	std::map<char, unsigned int> frequancies;
	read_data(in, data, frequancies);
	huffman_tree ht(frequancies);
	std::map<char, std::vector<bool>> table = ht.table;
	//write_table(table, out);  ------soon
	//write_data(data, table, out); -----------soon
}


void write_table(std::map<char, std::vector<bool>> table, std::ofstream& out){
	std::string bits_in_string = "";
	for (auto ch : table){
		for (int i = 0; i<bits_in_byte; i++){
			bits_in_string.push_back(get_bit_from_byte(ch.first, i));
		}
		uint8_t code_size = ch.second.size();
		for (int i = 0; i<bits_in_byte; i++){
			bits_in_string.push_back(get_bit_from_byte(code_size, i));
		}
		for (int i = 0; i<code_size; i++){
			bits_in_string.push_back(ch.second[i]);
		}
	}
	unsigned int size = (bits_in_string.size()-1)/8 + 1 + sizeof(unsigned int);
	std::string size_bits = "";
	for (int i=0; i<32; i++){
		bits_in_string.push_back(size%2);
		size /=2;
	}

}


void write_data(std::vector<char>& data, std::map<char, std::vector<bool>>& table, std::ofstream& out){
	std::string encoded_bits;
	for (auto byte: data){
		int code_size = table[byte].size();
		for (int i = 0; i< code_size; i++){
			encoded_bits.push_back(table[byte][i]);
		}
	}
}





void huffman_compressor::decompress(std::ifstream& in, std::ofstream& out){

}