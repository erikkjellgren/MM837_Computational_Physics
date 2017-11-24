/****************************************************************************
 * Program.cc
 * Main program for execution of Potts model
 * **************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include"iocontrol.h"
#include"Lattice.h"
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
	int L, q, thermalization_sweeps, simulation_sweeps, sample_frequency,
		sweep_method, hybrid_typewrite_freqency, random_seed;
	double beta;
	
	// Initialize iocontrol
	print_results results(1);
	results.write_input();
	
	// Load parameters from file
	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	L = j["L"];
	q = j["q"];
	thermalization_sweeps = j["thermalization_sweeps"];
	simulation_sweeps = j["simulation_sweeps"];
	sample_frequency = j["sample_frequency"];
	sweep_method = j["sweep_method"];
	hybrid_typewrite_freqency = j["hybrid_typewrite_freqency"];
	random_seed = j["random_seed"];
	beta = j["beta"];

	// Make container for energies
	vector<int> energy_container(simulation_sweeps/sample_frequency, 0);
	
	// Initialize lattice and sweeper method
	Lattice lattice_func(random_seed, L, q, beta, sweep_method);
	/*
	for (int i=0; i<thermalization_sweeps; i++){
		lattice_func.do_sweep();
	}
	*/
	for (int i=1; i<simulation_sweeps+1; i++){
		lattice_func.print_conf();
		lattice_func.calc_energy();
		lattice_func.do_sweep();
		if (i%sample_frequency == 0){
			energy_container[i/sample_frequency] = lattice_func.return_energy();
		}
	}
	
	// Calculate properties
	
	
	// Finalize IO
	results.close_files();
}
