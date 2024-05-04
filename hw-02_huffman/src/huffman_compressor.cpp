#include "huffman_compressor.h"

huffman_compressor::huffman_compressor(std::ifstream& in, std::ofstream& out): in(in), out(out) {}

void huffman_compressor::compress(){
	std::vector<char> data;
	std::map<char, unsigned int> frequencies;
    file_reader fr(in);
    file_writer fw(out);

	fr.read_file_compress(data, frequencies);
	huffman_tree ht(frequencies);
	ht.statistics.push_back(data.size());

	if (fw.is_useful(ht, ht.table, data)){
		fw.write_table(ht, ht.table);
		fw.write_data_compress(ht, data, ht.table);
	}
	ht.print_statistics();
}

void huffman_compressor::decompress(){
	std::vector<char> data;
	file_reader fr(in);
    file_writer fw(out);
    huffman_tree ht;
    fr.compressed_or_not_check();
    fr.read_file_decompress(ht, data);
    fw.write_data_decompress(data);
    ht.print_statistics();
}