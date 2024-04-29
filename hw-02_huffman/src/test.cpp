#if defined(DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN) && !defined(DOCTEST_CONFIG_IMPLEMENT)
#define DOCTEST_CONFIG_IMPLEMENT


#include "doctest.h"
#include "huffman_tree.h"
#include "huffman_compressor.h"
#include "args_parser.h"


TEST_CASE("huffman_node_test"){
	huffman_node node1;
	huffman_node node2('a', 123, &node1, nullptr);
	CHECK(node1.frequency==0);
	CHECK(node2.frequency==123);
	CHECK(node1.value=='\0');
	CHECK(node2.value=='a');
	CHECK(node2.left==&node1);
	CHECK(node2.right==nullptr);
	CHECK(node1.left==nullptr);
	CHECK(node1.right==nullptr);
}

TEST_CASE("empty_tree_test"){
	huffman_tree tree;
	CHECK(tree.get_size() == 0);
	CHECK(tree.root == nullptr);

TEST_CASE("building_tree_test"){
	huffman_tree tree;
	std::vector<char> empty_vector;
	CHECK(tree.get_size() == 0);
	CHECK(tree.root == nullptr);
	tree.build(empty_vector);
	CHECK(tree.get_size() == 0);
	CHECK(tree.root == nullptr);
	std::vector<char> v = {'a', 'b', 'c', 'b', 'a', 'a'};
	tree.build(v);
	CHECK(tree.root->value = 'c');
	Check(tree.root->frequency == 3);
}

TEST_CASE("encoding_test"){

}

TEST_CASE("decoding_test"){

}

TEST_CASE("statistics_test"){

}

TEST_CASE("save_to_file_test"){

}

TEST_CASE("encoding_decoding_test"){

}

TEST_CASE("parsing_args_test"){

}


#endif // DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN