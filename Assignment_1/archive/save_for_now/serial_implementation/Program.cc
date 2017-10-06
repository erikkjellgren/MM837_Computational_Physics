
#include<iostream>
#include<fstream>
#include<cmath>
#include "integrators.h"
#include "forces.h"
#include "printresults.h"
#include "properties.h"
#include"json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
	print_results results(0);
	results.checkInput(1);
	
	// assign all variables
	double mass, integration_step, delta, a, b, c, total_kinetic_energy, total_potential_energy;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global, number_steps, print_frequency;
	vector<double> position_x, velocity_x, acceleration_x, energy_vector;
	
	// load parameters in from world_rank == 0, communicate parameters
	// it is assumed that the parameter file only exist on the machine
	// with world_rank == 0

	ifstream ifs("parameters.json");
	json j = json::parse(ifs);
	a = j["a"];
	b = j["b"];
	c = j["c"];
	mass = j["mass"];
	delta = j["delta"];
	number_particles_global = j["number_particles"];
	number_steps = j["number_steps"];
	print_frequency = j["print_frequency"];
	integration_step = j["integration_step"];


	for (int i=0; i<number_particles_global; i++){
		position_x.push_back(0.0);
		velocity_x.push_back(sin(2.0*pi*((double)i+delta)/((double)number_particles_global)));
		acceleration_x.push_back(0.0);
	}

	integrators runIntegration(integration_step, number_particles_global);
	Forces runForces(a, b, c, number_particles_global, mass);
	calc_properties properties(number_particles_global, a, b, c, mass);

	for (int i=0; i<number_steps; i++){
		runForces.polynomicForce(position_x, acceleration_x);
		runIntegration.update_velocity(velocity_x, acceleration_x);
		runIntegration.update_position(position_x, velocity_x);
		runForces.polynomicForce(position_x, acceleration_x);
		runIntegration.update_velocity(velocity_x, acceleration_x);
		
		if (i%print_frequency == 0){
			energy_vector = properties.getEnergy(position_x, velocity_x);
			total_kinetic_energy = energy_vector[0];
			total_potential_energy = energy_vector[1];
			results.writeEnergy(total_kinetic_energy, total_potential_energy);				
		}
		
	}
	//results.close_output_files();
};