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

print_results::print_results(const int& run_ID_in, const int& L_in) :
	run_ID(run_ID_in), L(L_in){
	output_file = fopen(("output_"+to_string(run_ID)+".dat").c_str(),"w");
	int_autocorr_file = fopen(("int_autocorr_"+to_string(run_ID)+".dat").c_str(),"w");
	autocorr_file = fopen(("autocorr_"+to_string(run_ID)+".dat").c_str(),"w");
	energy_file = fopen(("energy_"+to_string(run_ID)+".dat").c_str(),"w");
	lattice_file = fopen(("lattice_"+to_string(run_ID)+".dat").c_str(),"w");
	two_point_corr_file = fopen(("two_point_corr_"+to_string(run_ID)+".dat").c_str(),"w");
}

void print_results::close_files(){
	fclose(output_file);
	fclose(int_autocorr_file);
	fclose(autocorr_file);
	fclose(energy_file);
	fclose(lattice_file);
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
	fprintf(output_file, "run_ID: ");
	fprintf(output_file, "%i", run_ID);
	fprintf(output_file, "\n");
	fprintf(output_file, "Actual random_seed = random_seed + run_ID");
	fprintf(output_file, "\n");
	fprintf(output_file, "\n");
}

void print_results::write_integrated_autocorr(const vector<double>& autocorr){
	for (int i=0; i<autocorr.size(); i++){
		fprintf(int_autocorr_file, "%f", autocorr[i]);
		fprintf(int_autocorr_file, "\n");
	}
}

void print_results::write_energy(const vector<double>& energy){
	for (int i=0; i<energy.size(); i++){
		fprintf(energy_file, "%f", energy[i]);
		fprintf(energy_file, "\n");
	}
}

void print_results::write_autocorr(const vector<double>& autocorr){
	for (int i=0; i<autocorr.size(); i++){
		fprintf(autocorr_file, "%f", autocorr[i]);
		fprintf(autocorr_file, "\n");
	}
}

void print_results::write_acceptance_ratio(const double& acceptance){
	fprintf(output_file, "%s", "Acceptance ratio: ");
	fprintf(output_file, "%f", acceptance);
	fprintf(output_file, "\n");
}

void print_results::write_lattice(const vector<vector<double>>& lattice){
	for (int i=0; i<L; i++){
		for (int j=0; j<L; j++){
			fprintf(lattice_file, "%f", lattice[i][j]);
			fprintf(lattice_file, " ");
		}
		fprintf(lattice_file, "\n");
	}
}

void print_results::write_two_point_corr(const vector<double>& two_point_vec){
	for (int i=0; i<two_point_vec.size(); i++){
		fprintf(two_point_corr_file, "%f", two_point_vec[i]);
		fprintf(two_point_corr_file, "\n");
	}
}