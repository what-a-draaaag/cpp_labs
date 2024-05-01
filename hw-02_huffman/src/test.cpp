#if defined(DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN) && !defined(DOCTEST_CONFIG_IMPLEMENT)
#define DOCTEST_CONFIG_IMPLEMENT


#include "doctest.h"
#include "huffman_tree.h"
#include "huffman_compressor.h"
#include "args_parser.h"


TEST_CASE("empty_tree_test"){
	huffman_tree tree1;
	CHECK(tree1.size() == 0);
	CHECK(tree1.code_vectors.size() == 0);
	CHECK(tree1.codes.size() == 0);

	std::map<char, unsigned int> frequencies = {};
	huffman_tree tree2(frequencies);
	CHECK(tree2.size() == 0);
	CHECK(tree2.code_vectors.size() == 0);
	CHECK(tree2.codes.size() == 0);

TEST_CASE("building_tree_test"){
	std::map<char, unsigned int> frequencies = {
		std::make_pair<'a', 123>,
		std::make_pair<'b', 103>,
		std::make_pair<'c', 2>,
	}
	huffman_tree tree(frequencies);
	CHECK(tree2.size() == 3);
	CHECK(tree2.code_vectors.size() == 3);
	CHECK(tree2.codes.size() == 3);;
}

TESTCASE("table_test"){
	std::map<char, unsigned int> frequencies = {
		std::make_pair<'a', 14>,
		std::make_pair<'b', 19>,
		std::make_pair<'c', 1>,
	}
	huffman_tree tree(frequencies);
	code_a = tree.table.codes['a'];
	code_b = tree.table.codes['b'];
	code_c = tree.table.codes['c'];

	CHECK(code_a == "01");
	CHECK(code_b == "1");
	CHECK(code_c == "00");

}

TEST_CASE("encoding_test"){
	std::map<char, unsigned int> frequencies = {
		std::make_pair<'a', 4>,
		std::make_pair<'b', 9>,
		std::make_pair<'c', 1>,
	}
	huffman_tree tree(frequencies);
	std::vector<char> data = {'a', 'a', 'c', 'b', 'b', 'b', 'a', 'b', 'b', 'b','b', 'a', 'b', 'b'};

	encoder enc(data, tree.table);
	CHECK(tree.table.codes['a'] == "01");
	CHECK(tree.table.codes['b'] == "1");
	CHECK(tree.table.codes['c'] == "00");
	std::vector<bool> encoded_data_expected = {0,1,0,1,0,0,1,1,1,0,1,1,1,1,1,0,1,1,1};
	CHECK(encoded_data_expected == enc.encode_data());


}

TEST_CASE("decoding_test"){

}

TEST_CASE("statistics_test"){

}

TEST_CASE("save_to_file_test"){

}

TEST_CASE("encoding_decoding_test"){

}

#endif // DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN