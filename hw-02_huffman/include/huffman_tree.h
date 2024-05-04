#pragma once
#include <istream>
#include <vector>
#include <map>
#include <algorithm>
#include <set>
#include <iostream>

class huffman_tree{
public:
	class Table{
	public:
		std::map<char, std::vector<bool>> code_vectors = {};
		std::map<char, std::string> char_to_code = {};
		std::map<std::string, char> code_to_char = {};
		std::vector<bool> bits ={};
		Table() = default;;

		std::string get_code(char ch);
		void make_codes();
		int get_code_len(char ch);
		int size();
		std::vector<bool> to_bits();
	};

	Table table;    	
	std::vector<int> statistics = {};
    void print_statistics();

	huffman_tree(std::map<char, unsigned int> frequancies);
	huffman_tree() = default;

};