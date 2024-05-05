#include "bin_controller.h"

const unsigned int bits_in_byte = 8;

uint8_t bin_controller::get_byte(std::vector<bool>& bits, unsigned int index) const{
	uint8_t res = 0;
	for (unsigned int i = 0; i< bits_in_byte; i++){
		if ((index*bits_in_byte+i)<bits.size()){
			res += bits[index*bits_in_byte+i] << (bits_in_byte-1-i);
		}
	}
	return res;
}

std::deque<bool> bin_controller::bytes_to_bits(std::vector<char>& bytes, unsigned int data_size) const{
	std::deque<bool> bits{};
	for (unsigned int i = 0; i< (bytes.size()*bits_in_byte); i++){
		bits.push_back(bytes[i/bits_in_byte]&(1<<((bits_in_byte-1-i)%bits_in_byte)));
	}
	bits.resize(data_size);
	return bits;
}


uint8_t bin_controller::get_first_byte(std::deque<bool>& bits) const{
	uint8_t res = 0;
	for (unsigned int i = 0; i< bits_in_byte; i++){
		if (i<bits.size()){
			res += bits[i] << (bits_in_byte - 1 -i);
		}
	}
	bits.erase(bits.begin(), bits.begin() + bits_in_byte);
	return res;
}