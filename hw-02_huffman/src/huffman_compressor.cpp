#include "huffman_compressor.h"
#include "huffman_tree.h"

void huffman_compressor::compress(std::ifstream& in, std::ofstream& out){
	std::vector<char> data;
	//char c;
	/*while (in >> c){
		data.push_back(c);
	}*/
	huffman_tree ht;
	ht.build(data);
	std::vector<char> table = ht.make_table();

}


void huffman_compressor::decompress(std::ifstream& in, std::ofstream& out){

}