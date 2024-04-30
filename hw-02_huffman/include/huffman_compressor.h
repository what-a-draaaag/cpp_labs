#pragma once
#include <vector>
#include <ostream>
#include <istream>



class huffman_compressor{
public:
    std::ifstream& in;
    std::ofstream& out;

    huffman_compressor(std::ifstream& in, std::ofstream& out);

    void compress();
    void decompress();  
};