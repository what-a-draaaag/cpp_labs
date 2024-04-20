#pragma once
#include <vector>
#include <ostream>
#include <istream>



class huffman_compressor{
public:
    void compress(std::vector<char>& data, std::ostream& out);
    void decompress(std::vector<char>& data, std::istream& in);  
};