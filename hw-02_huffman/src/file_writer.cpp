#include "file_writer.h"


const int bits_in_byte = 8;

file_writer::file_writer(std::ofstream& out): out(out), binc(bin_controller()) {}

bool file_writer::is_useful(huffman_tree& ht, huffman_tree::Table& table,  std::vector<char>& data) const{
	encoder enc(data, table);
	int data_size = data.size();
	int table_size = (table.size()-1)/8+1;
	int sizes_values_size = 2*sizeof(unsigned int);
	int encoded_data_size = (enc.encode_data().size()-1)/bits_in_byte+1;
	if (data_size<= (table_size+sizes_values_size+encoded_data_size)){
		ht.statistics.push_back(data_size);
		ht.statistics.push_back(0);
		for (char ch: data){
			out.put(ch);
		}
		return false;
	}
	ht.statistics.push_back(encoded_data_size);
	ht.statistics.push_back(table_size+sizes_values_size);
	return true;
}


void file_writer::write_table(huffman_tree& ht, huffman_tree::Table& table) const{
	unsigned int size_of_table = table.size();
	out.write(reinterpret_cast<char const*>(&size_of_table), sizeof(unsigned int));
	write_vector(table.bits);
}

void file_writer::write_data_compress(huffman_tree& ht, std::vector<char>& data, huffman_tree::Table& table) const{
	encoder enc(data, table);
	std::vector<bool> encoded_data = enc.encode_data();
	unsigned int size_of_data = encoded_data.size();
	out.write(reinterpret_cast<const char*>(&size_of_data), sizeof(unsigned int));
	write_vector(encoded_data);
	
}

void file_writer::write_vector(std::vector<bool>& v) const{
	unsigned int size_in_bytes = (v.size()-1)/bits_in_byte +1;
	for (unsigned int i = 0; i< size_in_bytes; i++){
		uint8_t byte = binc.get_byte(v, i);
		out.put(byte);
	}
}

void file_writer::write_data_decompress(std::vector<char>& data) const{
	for (char ch : data){
		out.put(ch);
	}
}
