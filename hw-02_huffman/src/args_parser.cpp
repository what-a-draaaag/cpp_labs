#include "args_parser.h"

void args_parser::parse(int argc, char** argv){
	action = unknown;
	arg = flag;
	for (int i = 0; i < argc; ++i)
	{
		if (!strcmp(argv[i], "-c")){
			action = compress;
			continue;
		}
		if (!strcmp(argv[i], "-u")){
			action = decompress;
			continue;
		}
		if (strcmp(argv[i], "--file")==0 || strcmp(argv[i], "-f")==0){
			arg = input_filename;
			continue;
		}
		if (strcmp(argv[i], "--output")==0 || strcmp(argv[i], "-o")==0){
			arg = output_filename;
			continue;
		}
		if (arg == input_filename){
			fin_name = argv[i];
			continue;
		}
		if (arg == output_filename){
			fout_name = argv[i];
			continue;
		}
	}
}