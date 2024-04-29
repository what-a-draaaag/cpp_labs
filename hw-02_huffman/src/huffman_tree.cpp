#include "huffman_tree.h"

huffman_tree::huffman_tree(std::map<char, unsigned int> frequancies){
	std::set<std::pair<std::vector<char>, unsigned int>> tree;
	for (auto symbol : frequancies){
		std::vector<char> ch{symbol.first};
		tree.insert(std::make_pair(ch, symbol.second));
	}
	while (tree.size()>1){
		std::pair<std::vector<char>, unsigned int> first = *tree.begin();
		tree.erase(first);
		std::pair<std::vector<char>, unsigned int> second = *tree.begin();
		tree.erase(second);
		for (auto ch : first.first){
			table[ch].push_back(0);
		}
		for (auto ch : second.first){
			table[ch].push_back(1);
		}
		std::vector<char> new_elem = first.first;
		new_elem.insert(new_elem.end(), second.first.begin(), second.first.end());
		tree.insert(std::make_pair(new_elem, first.second+second.second));
	}

	for (auto pair: tree){
		std::reverse(pair.first.begin(), pair.first.end());
	}
}