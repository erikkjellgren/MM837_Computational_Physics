/*****************************************************************************
 * iocontrol.h
 * Headerfile for ionctrol.cc
 * ***************************************************************************/
#ifndef _IOCONTROL_H_
#define _IOCONTROL_H_
 
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
};
#endif