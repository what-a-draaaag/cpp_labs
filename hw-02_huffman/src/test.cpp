#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "huffman_tree.h"
#include "huffman_compressor.h"
#include <fstream>

const int bits_in_byte = 8;

TEST_CASE("empty_tree_test"){
	huffman_tree tree1;
	CHECK(tree1.table.size() == 0);
	CHECK(tree1.table.code_vectors.size() == 0);
	CHECK(tree1.table.char_to_code.size() == 0);

	std::map<char, unsigned int> frequencies = {};
	huffman_tree tree2(frequencies);
	CHECK(tree2.table.size() == 0);
	CHECK(tree2.table.code_vectors.size() == 0);
	CHECK(tree2.table.char_to_code.size() == 0);
}

TEST_CASE("building_tree_test"){
	std::map<char, unsigned int> frequencies = {};
	frequencies.insert(std::make_pair('a', 123));
	frequencies.insert(std::make_pair('b', 103));
	frequencies.insert(std::make_pair('c', 2));
	huffman_tree tree(frequencies);

	unsigned int expected_table_size = sizeof(char)*3*2*bits_in_byte + sizeof(char)*2*2 + sizeof(char);
	CHECK(tree.table.size() == expected_table_size);
	CHECK(tree.table.code_vectors.size() == frequencies.size());
	CHECK(tree.table.char_to_code.size() == frequencies.size());
}

TEST_CASE("table_test"){
	std::map<char, unsigned int> frequencies = {};
	frequencies.insert(std::make_pair('a', 14));
	frequencies.insert(std::make_pair('b', 19));
	frequencies.insert(std::make_pair('c', 1));
	huffman_tree tree(frequencies);

	std::string code_a = tree.table.char_to_code['a'];
	std::string code_b = tree.table.char_to_code['b'];
	std::string code_c = tree.table.char_to_code['c'];

	CHECK(strcmp(code_a.c_str(),"\0\1") == 0);
	CHECK(strcmp(code_b.c_str(),"\1") == 0);
	CHECK(strcmp(code_c.c_str(),"\0\0") == 0);

}

TEST_CASE("encoding_test"){
	std::map<char, unsigned int> frequencies = {};
	frequencies.insert(std::make_pair('a', 4));
	frequencies.insert(std::make_pair('b', 9));
	frequencies.insert(std::make_pair('c', 1));
	huffman_tree tree(frequencies);
	std::vector<char> data = {'a', 'a', 'c', 'b', 'b', 'b', 'a', 'b', 'b', 'b','b', 'a', 'b', 'b'};

	encoder enc(data, tree.table);
	std::string code_a = tree.table.char_to_code['a'];
	std::string code_b = tree.table.char_to_code['b'];
	std::string code_c = tree.table.char_to_code['c'];

	CHECK(strcmp(tree.table.char_to_code['a'].c_str(),"\0\0") == 0) ;
	CHECK(strcmp(tree.table.char_to_code['b'].c_str(),"\1") == 0);
	CHECK(strcmp(tree.table.char_to_code['c'].c_str(),"\0\1") == 0);

	std::vector<bool> encoded_data_expected = {0,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1};
	CHECK(encoded_data_expected == enc.encode_data());
}

TEST_CASE("decoding_test"){

}

TEST_CASE("empty_file_compress"){
	std::ifstream fin("./samples/empty1.txt");
	std::ofstream fout("./samples/empty2.txt");
	huffman_compressor compressor(fin, fout);
	compressor.compress();
	fout.seekp(0, std::ios::end);
	CHECK(fout.tellp() == 0);
}

TEST_CASE("empty_file_decompress"){
	std::ifstream fin("./samples/empty2.txt");
	std::ofstream fout("./samples/empty3.txt");
	huffman_compressor compressor(fin, fout);
	compressor.decompress();
	fout.seekp(0, std::ios::end);
	CHECK(fout.tellp() == 0);
}

TEST_CASE("useful_compress_test"){
	std::ifstream fin("./samples/comp1.txt");
	std::ofstream fout("./samples/comp2.txt");
	huffman_compressor compressor(fin, fout);
	compressor.compress();
	
	fout.close();
	fin.close();
	std::vector<char> data1{};
	std::vector<char> data2{};

	std::ifstream fout_read("./samples/comp2.txt");
	std::ifstream fin_read("./samples/comp1.txt");

	char elem;
	while (fin_read.get(elem)){
		data1.push_back(elem);
	}
	while (fout_read.get(elem)){
		data2.push_back(elem);
	}
	CHECK(data2.size()>0);
	CHECK(data1.size() >= data2.size());
}

TEST_CASE("useless_compress_test"){
	std::ifstream fin("./samples/comp3.txt");
	std::ofstream fout("./samples/comp4.txt");
	huffman_compressor compressor(fin, fout);
	compressor.compress();

	fout.close();
	fin.close();

	std::vector<char> data1{};
	std::vector<char> data2{};
	char ch;
	
	std::ifstream fout_read("./samples/comp4.txt");
	std::ifstream fin_read("./samples/comp3.txt");
	while (fin_read.get(ch)){
		data1.push_back(ch);
	}
	while (fout_read.get(ch)){
		data2.push_back(ch);
	}
	CHECK(data2.size()>0);
	CHECK(data1.size() == data2.size());
}

TEST_CASE("compressed_file_decompress"){
	std::ifstream fin("./samples/comp2.txt");
	std::ofstream fout("./samples/decomp1.txt");
	huffman_compressor compressor(fin, fout);
	compressor.decompress();
	fout.close();
	std::ifstream fout_read("./samples/decomp1.txt");
	std::ifstream fin_expected_decomp("./samples/comp1.txt");

	std::vector<char> result {};
	std::vector<char> expected {};

	char elem;
	while(fout_read.get(elem)){
		result.push_back(elem);
	}
	while (fin_expected_decomp.get(elem)){
		expected.push_back(elem);
	}

	CHECK(result == expected);
}

TEST_CASE("not_compressed_file_decompress"){
	std::ifstream fin("./samples/comp4.txt");
	std::ofstream fout("./samples/decomp2.txt");
	huffman_compressor compressor(fin, fout);
	compressor.decompress();

	std::vector<char> result {};
	std::vector<char> expected {};
	fout.close();
	std::ifstream fout_read("./samples/decomp2.txt");
	std::ifstream fin_expected_decomp("./samples/comp3.txt");

	char elem;
	while(fout_read.get(elem)){
		result.push_back(elem);
	}
	while (fin_expected_decomp.get(elem)){
		expected.push_back(elem);
	}

	CHECK(result == expected);
}

TEST_CASE("bit_byte_operations"){
	bin_controller binc;

	std::vector<char> bytes {'a', 'b', 'c'};
	std::deque<bool> bits = binc.bytes_to_bits(bytes, bytes.size()*bits_in_byte);

	std::deque<bool> expected_bits {0,0,1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,1,1,1,1,1,1};

	CHECK(bits == expected_bits);
	//get_byte
	//get_first_byte
}

TEST_CASE("compress_decompress_equal"){
	std::ifstream fin1("./samples/sample1.txt");
	std::ofstream fout1("./samples/sample2.txt");
	std::ifstream fin2("./samples/sample2.txt");
	std::ofstream fout2("./samples/sample3.txt");

	huffman_compressor compressor(fin1, fout1);
	compressor.compress();
	fout1.close();
	huffman_compressor decompressor(fin2, fout2);
	decompressor.decompress();
	fin1.seekg(0, std::ios::beg);

	std::vector<char> data1{};
	char ch;
	while (fin1.get(ch)){
		data1.push_back(ch);
	}

	std::vector<char> data2{};
	std::ifstream fout2_read("./samples/sample3.txt");
	while (fout2_read.get(ch)){
		data2.push_back(ch);
	}

	CHECK(data1 == data2);
}

