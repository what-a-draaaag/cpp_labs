# pragma once

#include <deque>
#include <cstdint>
#include <vector>



class bin_controller{
public:

	bin_controller() = default;

	uint8_t get_byte(std::vector<bool>& bits, unsigned int index) const;
	std::deque<bool> bytes_to_bits(std::vector<char>& bytes, unsigned int data_size) const;
	uint8_t get_first_byte(std::deque<bool>& bits) const;
};