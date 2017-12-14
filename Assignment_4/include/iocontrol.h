/*****************************************************************************
 * iocontrol.h
 * Headerfile for ionctrol.cc
 * ***************************************************************************/
#ifndef _IOCONTROL_H_
#define _IOCONTROL_H_
 
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

class print_results{
	private:
		FILE* output_file;
		FILE* energy_file;
		const int run_ID;
	public:
		print_results(const int& run_ID_in);
		void close_files();
		void write_input();
		void write_energy(const vector<double>& energy);
};
#endif