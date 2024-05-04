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
		int get_code_len(char ch);
		int size() const;

		std::vector<bool> to_bits();
		void make_codes();
	private:
		bool get_bit_from_byte(char byte, int index) const;
		};

	huffman_tree() = default;
	huffman_tree(std::map<char, unsigned int> frequancies);

	Table table;    	
	std::vector<int> statistics = {};
    void print_statistics() const;

};