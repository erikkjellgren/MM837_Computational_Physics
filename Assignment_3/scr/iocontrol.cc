/*****************************************************************************
 * iocontrol.cc
 * Contains methods to print outputs to files
 * ***************************************************************************/
 
#include<fstream>
#include<string>
#include"json.hpp"
#include"iocontrol.h"

using namespace std;
using json = nlohmann::json;

print_results::print_results(const int& to_please_cpp_in){
	to_please_cpp = to_please_cpp_in;
	output_file = fopen("output.dat","w");
}

void print_results::close_files(){
	fclose(output_file);
}

void print_results::write_input(){
	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	
	//write out input
	string s = j.dump(4);
	fprintf(output_file, "Inputfile:");
	fprintf(output_file, "\n");
	fprintf(output_file, "%s", s.c_str());
	fprintf(output_file, "\n");
	fprintf(output_file, "\n");
}