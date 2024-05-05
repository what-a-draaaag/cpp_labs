#include "decoder.h"

decoder::decoder(std::deque<bool>& encoded_data, huffman_tree::Table& table):encoded_data(encoded_data), table(table) {}

std::vector<char> decoder::decode_data(){
	std::vector<char> decoded_data{};
	int data_size = encoded_data.size();
	std::string code = "";
	for (int i = 0; i<data_size; i++){
		if (encoded_data[i]){
			code.push_back('1');
		}
		else
			code.push_back('0');
		if (table.code_to_char.contains(code)){
			decoded_data.push_back(table.code_to_char[code]);
			code = "";
		}
	}
	return decoded_data;
}