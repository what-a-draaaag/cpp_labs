#pragma once
#include <string>
#include <cstring>


enum action_type{
	compress,
	decompress,
	unknown,
};

enum arg_type{
	output_filename,
	input_filename,
	flag,
};

class args_parser{
public:
	void parse(int argc, char** argv);
	std::string fin_name;
	std::string fout_name;
	action_type action;
	arg_type arg;
};
