/*****************************************************************************
 * iocontrol.h
 * Headerfile for ionctrol.cc
 * ***************************************************************************/

#include<fstream>
#include<string>
#include"json.hpp"

class print_results{
	public:
		void close_files();
		void write_input();
		void fatal_error(const int& error_code);
};