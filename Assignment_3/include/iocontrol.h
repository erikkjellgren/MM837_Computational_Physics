/*****************************************************************************
 * iocontrol.h
 * Headerfile for ionctrol.cc
 * ***************************************************************************/


#include<fstream>
#include<string>
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

class print_results{
	private:
		FILE* output_file;
		int to_please_cpp;
	public:
		print_results(const int& to_please_cpp_in);
		void close_files();
		void write_input();
		void fatal_error(const int& error_code);
};