#include "huffman_compressor.h"
#include "huffman_tree.h"
#include "file_writer.h"
#include <fstream>



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
	ht.table.to_bits();
	ht.table.make_codes();
	file_writer fw(out);
	fw.write_table(ht.table);
	fw.write_data(data, ht.table);
}






void huffman_compressor::decompress(std::ifstream& in, std::ofstream& out){

}