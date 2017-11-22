/****************************************************************************
 * Program.cc
 * Main program for execution of Potts model
 * **************************************************************************/

#include<iostream>
#include<fstream>
#include "iocontrol.h"
#include "Sweepers.h"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
	int L, q, thermalization_sweeps, simulation_sweeps, sample_frequency,
		sweep_method, hybrid_typewrite_freqency, random_seed;
	
	// Initialize iocontrol
	print_results results(1);
	results.write_input();
	
	// Load parameters from file
	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	L = j["L"];
	q = j["q"];
	thermalization_sweeps = j["thermalization_steps"];
	simulation_sweeps = j["simulation_steps"];
	sample_frequency = j["sample_frequency"];
	sweep_method = j["sweep_method"];
	hybrid_typewrite_freqency = j["hybrid_typewrite_freqency"]
	random_seed = j["random_seed"]
	
	// Initialize lattice and sweeper method
	if (sweep_method == 1){;}
	else if (sweep_method == 2){;}
	else if (sweep_method == 3){;}
	else {
		results.fatal_error(1);
		exit (EXIT_FAILURE);
	}
	
	for (int i=0; i<thermalization_sweeps; i++){
		
	}
	
	for (int i=1; i<simulation_sweeps+1; i++){
		
		if (i%sample_frequency == 0){;}
		
	}
	
	// Calculate properties
	
	
	// Finalize IO
	results.close_files();
	
	
}
