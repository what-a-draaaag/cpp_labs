#include "file_reader.h"

const int bits_in_byte = 8;

file_reader::file_reader(std::ifstream& in): in(in) {}

void file_reader::read_file_compress(std::vector<char>& data, std::map<char, unsigned int>& frequencies){
	char c;
	while (in.get(c)){
		data.push_back(c);
		frequencies[c]++;
	}
}


std::deque<bool> file_reader::bytes_to_bits(std::vector<char>& bytes){
	std::deque<bool> bits{};
	for (unsigned int i = 0; i< (bytes.size()*bits_in_byte); i++){
		bits.push_back(bytes[i/bits_in_byte]&(1<<((bits_in_byte-1-i)%bits_in_byte)));
	}
	bits.resize(data_size_in_bits);
	return bits;
}

void file_reader::compressed_or_not_check(){
	in.seekg(0, std::ios_base::end);
	unsigned int size_of_file = in.tellg();

	in.seekg(0, std::ios_base::beg);
    unsigned int table_size;
    in.read(reinterpret_cast<char*>(&table_size), sizeof(table_size));
    table_size_in_bytes = (table_size-1)/bits_in_byte +1;
    in.seekg(table_size_in_bytes, std::ios::cur);
   	if (in.tellg()>= size_of_file) return;
    in.read(reinterpret_cast<char*>(&data_size_in_bits), sizeof(data_size_in_bits));

    data_size_in_bytes = (data_size_in_bits-1)/bits_in_byte +1;
    in.seekg(data_size_in_bytes, std::ios::cur);
    if (in.tellg() == size_of_file) {
    	file_is_compressed = true;
    	return;
    }    
}

void file_reader::read_file_decompress(huffman_tree& ht, std::vector<char>& decoded_data){
	if (file_is_compressed){
		read_table(ht);
		std::vector<char> data = read_data();
		std::deque<bool> data_bits = bytes_to_bits(data);
		decoder dec(data_bits, ht.table);
		ht.statistics.push_back(data_size_in_bytes);
		ht.statistics.push_back(decoded_data.size());
		ht.statistics.push_back(table_size_in_bytes+2*sizeof(unsigned int));

		decoded_data = dec.decode_data();
	}
	else{
		decoded_data = read_not_compressed_data();
		ht.statistics.push_back(decoded_data.size());
		ht.statistics.push_back(decoded_data.size());
		ht.statistics.push_back(0);
	}
}

uint8_t get_first_byte(std::deque<bool>& bits){
	uint8_t res = 0;
	for (unsigned int i = 0; i< bits_in_byte; i++){
		if (i<bits.size()){
			res += bits[i] << (bits_in_byte - 1 -i);
		}
	}
	bits.erase(bits.begin(), bits.begin() + bits_in_byte);
	return res;
}

void file_reader::read_table(huffman_tree& ht){
    std::vector<char> table_bytes{};
    in.seekg(sizeof(unsigned int), std::ios::beg);

	while (static_cast<unsigned int>(in.tellg())< (table_size_in_bytes + sizeof(unsigned int))){
		char byte;
		in.get(byte);
		table_bytes.push_back(byte);
	}
	std::deque<bool> table_bits = bytes_to_bits(table_bytes);
	while (static_cast<long int>(table_bits.size()) > 0) {
		char ch = get_first_byte(table_bits);
		uint8_t code_len = get_first_byte(table_bits);
		std::string code = "";
		for (unsigned int i = 0; i< code_len; i++){
			code.push_back(table_bits[0]);
			table_bits.pop_front();
		}
		ht.table.char_to_code.insert(std::make_pair(ch, code));
		ht.table.code_to_char.insert(std::make_pair(code, ch));
	}
}

std::vector<char> file_reader::read_data(){
	std::vector<char> data;
	in.seekg(table_size_in_bytes+sizeof(unsigned int)*2);
	for (unsigned int i = 0; i< data_size_in_bytes; i++){
		data.push_back(in.get());
	}
	return data;
}

std::vector<char> file_reader::read_not_compressed_data(){
	std::vector<char> data;
	char elem;
	in.seekg(0, std::ios::beg);
	while (in.get(elem)){
		data.push_back(elem);
	}
	return data;
}

