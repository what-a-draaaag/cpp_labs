#include "encoder.h"

encoder::encoder(std::vector<char>& data, huffman_tree::Table& table): data(data), table(table) {}

std::vector<bool> encoder::encode_data(){
	std::vector<bool> encoded_bits;
	for (auto ch: data){
		int code_size = table.get_code_len(ch);
		std::string code = table.get_code(ch);
		for (int i = 0; i< code_size; i++){
			if (code[i] == '1')
				encoded_bits.push_back(1);
			else
				encoded_bits.push_back(0);
		}
	}
	return encoded_bits;
}