/****************************************************************************
 * Program.cc
 * Main program for execution of Potts model
 * **************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
#include"iocontrol.h"
#include"Lattice.h"
#include"Properties.h"
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
	int L, thermalization_sweeps, simulation_sweeps, sample_frequency,
		sweep_method, typewriter_freqency, random_seed,
		autocorrelation_cut, replications;
	double beta, acceptance_ratio, delta_range;
	
	// Load parameters from file
	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	L = j["L"];
	thermalization_sweeps = j["thermalization_sweeps"];
	simulation_sweeps = j["simulation_sweeps"];
	sample_frequency = j["sample_frequency"];
	sweep_method = j["sweep_method"];
	typewriter_freqency = j["typewriter_freqency"];
	random_seed = j["random_seed"];
	beta = j["beta"];
	autocorrelation_cut = j["autocorrelation_cut"];
	replications = j["replications"];
	delta_range = j["delta_range"];
	
	#pragma omp parallel for schedule(dynamic)
	for (int run_ID=0; run_ID<replications; run_ID++){
		// Initialize iocontrol
		print_results results(run_ID, L);
		results.write_input();
		random_seed += run_ID;
		
		// Make container for energies
		vector<double> energy_container(simulation_sweeps/sample_frequency, 0);
		
		// Initialize lattice and sweeper method
		Lattice lattice_func(random_seed, L, beta, sweep_method, typewriter_freqency, delta_range);

		for (int i=0; i<thermalization_sweeps; i++){
			lattice_func.do_sweep();
		}

		for (int i=1; i<simulation_sweeps+1; i++){
			lattice_func.do_sweep();
			if (i%sample_frequency == 0){
				energy_container[i/sample_frequency-1] = lattice_func.return_energy();
				//results.write_lattice(lattice_func.return_lattice());
			}
		}
		
		results.write_acceptance_ratio(lattice_func.return_acceptance_ratio());
		// Calculate properties
		properties property_func(energy_container, autocorrelation_cut);
		property_func.calc_autocorrelation();
		property_func.calc_integrated_autocorr();
		results.write_energy(energy_container);
		results.write_integrated_autocorr(property_func.return_integrated_autocorr());
		results.write_autocorr(property_func.return_autocorr());
		
		// Finalize IO
		results.close_files();
	}
}