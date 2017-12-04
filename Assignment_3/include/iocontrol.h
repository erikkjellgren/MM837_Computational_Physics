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
		FILE* int_autocorr_file;
		FILE* autocorr_file;
		FILE* energy_file;
		int to_please_cpp;
	public:
		print_results(const int& to_please_cpp_in);
		void close_files();
		void write_input();
		void write_integrated_autocorr(const vector<double>& autocorr);
		void write_autocorr(const vector<double>& autocorr);
		void write_energy(const vector<double>& energy);
		void write_acceptance_ratio(const double& acceptance);
};
#endif