#pragma once
#include <vector>
#include <ostream>
#include <istream>
#include "huffman_tree.h"
#include "file_writer.h"
#include "file_reader.h"
#include <fstream>



class huffman_compressor{
public:
    std::ifstream& in;
    std::ofstream& out;

    huffman_compressor(std::ifstream& in, std::ofstream& out);

    void compress();
    void decompress();  
};