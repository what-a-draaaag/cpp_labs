#include "file_writer.h"


const int bits_in_byte = 8;

file_writer::file_writer(std::ofstream& out): out(out) {}


uint8_t get_byte(std::vector<bool> bits, unsigned int index){
	uint8_t res = 0;
	for (unsigned int i = 0; i< bits_in_byte; i++){
		if ((index*bits_in_byte+i)<bits.size())
			res += bits[index*bits_in_byte+i] * pow(2, 7-i);
	}

	//BUGS????


	return res;
}


std::vector<bool> encode_data(std::vector<char>& data, huffman_tree::Table& table){
	std::vector<bool> encoded_bits;
	for (auto ch: data){
		int code_size = table.get_code_len(ch);
		std::string code = table.get_code(ch);
		for (int i = 0; i< code_size; i++){
			encoded_bits.push_back(code[i]);
		}
	}
	return encoded_bits;
}


void file_writer::write_table(huffman_tree::Table& table){
	unsigned int size_of_table = table.size();
	out.write(reinterpret_cast<const char*>(size_of_table), 4);
	unsigned int size_in_bytes = (size_of_table-1)/8 +1;
	for (unsigned int i = 0; i< size_in_bytes; i++){
		uint8_t byte = get_byte(table.bits, i);
		out.put(byte);
	}
}

void file_writer::write_data(std::vector<char>& data, huffman_tree::Table& table){
	std::vector<bool> encoded_data = encode_data(data, table);
	unsigned int size_of_data = encoded_data.size();
	out.write(reinterpret_cast<const char*>(size_of_data), 4);
	unsigned int size_in_bytes = (size_of_data-1)/8 +1;
	for (unsigned int i = 0; i< size_in_bytes; i++){
		uint8_t byte = get_byte(encoded_data, i);
		out.put(byte);
	}
	
}

