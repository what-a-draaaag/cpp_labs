
#include "huffman_tree.h"
#include "huffman_compressor.h"
#include "args_parser.h"
#include <iostream>
#include <fstream>

int main(int argc, char** argv){
	args_parser parser;
	try{
		parser.parse(argc, argv);
	}
	catch(std::exception& e){
		std::cout << "Parsing failed: " <<e.what() << std::endl;
		return 0;
	}
	if (parser.fin_name.length() == 0 || parser.fout_name.length() == 0){
		std::cout << "Input/output filename not given." << std::endl;
		return 0;
	}
	std::ifstream fin(parser.fin_name);
	std::ofstream fout(parser.fout_name);

	if (!fin.is_open() || ! fout.is_open()){
		std::cout << "Opening files failed." << std::endl;
		return 0;
	}

	huffman_compressor compressor(fin, fout);

	if (parser.action == compress){
		compressor.compress();
	}
	else if (parser.action == decompress){
		compressor.decompress();
	}
	else{
		std::cout << "Type of processing files is unknown."<<std::endl;
		return 0;
	}
	return 0;
}