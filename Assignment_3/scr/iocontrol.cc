/*****************************************************************************
 * iocontrol.cc
 * Contains methods to print outputs to files
 * ***************************************************************************/
 
#include<fstream>
#include<string>
#include<vector>
#include"json.hpp"
#include"iocontrol.h"

using namespace std;
using json = nlohmann::json;

print_results::print_results(const int& to_please_cpp_in){
	to_please_cpp = to_please_cpp_in;
	output_file = fopen("output.dat","w");
	autocorr_file = fopen("autocorr.dat","w");
	energy_file = fopen("energy.dat","w");
}

void print_results::close_files(){
	fclose(output_file);
	fclose(autocorr_file);
	fclose(energy_file);
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

void print_results::write_integrated_autocorr(const vector<double>& autocorr){
	for (int i=0; i<autocorr.size(); i++){
		fprintf(autocorr_file, "%f", autocorr[i]);
		fprintf(autocorr_file, "\n");
	}
}

void print_results::write_energy(const vector<int>& energy){
	for (int i=0; i<energy.size(); i++){
		fprintf(energy_file, "%i", energy[i]);
		fprintf(energy_file, "\n");
	}
}