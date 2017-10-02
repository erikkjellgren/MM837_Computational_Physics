
#include <mpi.h>
#include<iostream>
#include<cmath>
#include "integrators.h"
#include "forces.h"
#include "printresults.h"
#include "properties.h"

using namespace std;

int main(){
	// initialize the MPI
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	// make so parameters can be loaded from parameter file
	// load parameters in from world_rank == 0, and communicate out
	double mass=1.0, integration_step=0.01, delta=0.1, a=1.0, b=0.0, c=0.0;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global=10, steps=10000, number_particles_local,  print_frequency=1;
	vector<double> position_x, velocity_x, acceleration_x;
	
	// assign number_particles_local
	// Setup the system
	for (int i=0; i<number_particles_local; i++){
		position_x.push_back(0.0);
		// fix so the initial velocties are distributed the right way.
		// distribution should be identical for many processes, as for 
		// one process
		velocity_x.push_back(sin(2.0*pi*((double)i+delta)/((double)number_particles_local)));
		acceleration_x.push_back(0.0);
	}
	
	// initialize all the classes
	// the classes are just used as containers of functions, such
	// that constants dosen't need to be given as argument every time.
	integrators runIntegration(integration_step, number_particles_local);
	Forces runForces(a, b, c, number_particles_local, mass);
	calc_properties properties(number_particles_local, a, b, c, mass);
	if (world_rank == 0){print_results results(number_particles_global);} 
	
	for (int i=0; i<steps; i++){
		runForces.polynomicForce(position_x, acceleration_x);
		// communicate that single force
		MPI_Send();
		MPI_Recv();
		runIntegration.update_velocity(velocity_x, acceleration_x);
		runIntegration.update_position(position_x, velocity_x);
		runForces.polynomicForce(position_x, acceleration_x);
		// communicate that single force
		MPI_Send();
		MPI_Recv();
		runIntegration.update_velocity(velocity_x, acceleration_x);
		if (i%print_frequency == 0){
			energy_vector = properties.getEnergy(position_x, velocity_x);
			// communicate energy_vector
			if (world_rank != 0){
				MPI_Send();
			}
			if (world_rank == 0){
				MPI_Recv();
			}
		}
		
	}
	if (world_rank == 0){results.close_output_files();}
};