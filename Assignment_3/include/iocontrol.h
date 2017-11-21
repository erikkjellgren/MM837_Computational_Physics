/*****************************************************************************
 * iocontrol.h
 * Headerfile for ionctrol.cc
 * ***************************************************************************/

#include<fstream>
#include<string>
#include"json.hpp"

using namespace std;

class print_results{
	public:
		void close_files();
		void write_input();
};