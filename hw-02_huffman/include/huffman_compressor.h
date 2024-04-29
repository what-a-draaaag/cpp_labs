#pragma once
#include <vector>
#include <ostream>
#include <istream>



class huffman_compressor{
public:
    void compress(std::ifstream& in, std::ofstream& out);
    void decompress(std::ifstream& in, std::ofstream& out);  
};