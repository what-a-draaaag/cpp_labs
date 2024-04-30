#include "huffman_compressor.h"
#include "huffman_tree.h"
#include "file_writer.h"
#include <fstream>

huffman_compressor::huffman_compressor(std::ifstream& in, std::ofstream& out): in(in), out(out) {}

void read_data(std::ifstream& in, std::vector<char>& data, std::map<char, unsigned int>& frequencies){
	char c;
	while (in.get(c)){
		data.push_back(c);
		frequencies[c]++;
	}
}



void huffman_compressor::compress(){
	std::vector<char> data;
	std::map<char, unsigned int> frequencies;
	read_data(in, data, frequencies);
	huffman_tree ht(frequencies);

	ht.statistics.push_back(data.size());
	ht.table.to_bits();
	ht.table.make_codes();
	file_writer fw(out);
	fw.write_table(ht, ht.table);
	fw.write_data(ht, data, ht.table);
	ht.print_statistics();
}






void huffman_compressor::decompress(){

}