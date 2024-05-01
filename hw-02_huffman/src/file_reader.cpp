#include "file_reader.h"

file_reader::file_reader(std::ifstream& in): in(in) {}

void file_reader::read_file_compress(std::vector<char>& data, std::map<char, unsigned int>& frequencies){
	char c;
	while (in.get(c)){
		data.push_back(c);
		frequencies[c]++;
	}
}

bool file_reader::is_compressed(){
	if (in.eof()){
		return false;		
	}
	try{
		unsigned int size_of_table = in.get();
		in.seekg(size_of_table - 4);
		if (in.eof()){
			return false;
		}
		unsigned int size_of_data = in.get();
		in.seekg(size_of_data-1);
		if (in.eof()){
			return false;
		}
		in.seekg(1);
		if (in.eof()){
			return true;
		}
	}
	catch(...){
		return false;
	}
	return false;

	//NOT WORKING CORRECTLY
}

void file_reader::read_file_decompress(huffman_tree& ht, std::vector<char>& data){
	//unsigned int size_of_table = in.get();
	//std::vector<char> table_bytes;
	// TO BE CONTINUED
}