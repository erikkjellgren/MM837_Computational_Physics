
#include<mpi.h>
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
	
	// initialize the output class
	if (world_rank == 0){print_results results();} 
	results.checkInput(world_size);
	
	// assign all variables
	double mass, integration_step, delta, a, b, c, recv_buffer;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global, number_steps, number_particles_local, print_frequency;
	vector<double> position_x, velocity_x, acceleration_x;
	
	// load parameters in from world_rank == 0, communicate parameters
	// it is assumed that the parameter file only exist on the machine
	// with world_rank == 0
	if (world_rank==0){
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
		// pretty ugly way to send it out. There must be
		// a better solution. 
		for (int i=1; i<world_size; i++){
			MPI_Send(&a,1,MPI_DOUBLE,i,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&b,1,MPI_DOUBLE,i,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&c,1,MPI_DOUBLE,i,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&mass,1,MPI_DOUBLE,i,4,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&delta,1,MPI_DOUBLE,i,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&number_particles_global,1,MPI_INT,i,6,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&number_steps,1,MPI_INT,i,7,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Send(&print_frequency,1,MPI_INT,i,8,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
	}
	// 
	if (world_rank!=0){
			MPI_Recv(&a,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&b,1,MPI_DOUBLE,0,2,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&c,1,MPI_DOUBLE,0,3,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&mass,1,MPI_DOUBLE,0,4,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&delta,1,MPI_DOUBLE,0,5,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&number_particles_global,1,MPI_INT,0,6,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&number_steps,1,MPI_INT,0,7,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			MPI_Recv(&print_frequency,1,MPI_INT,0,8,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}

	
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
	
	for (int i=0; i<number_steps; i++){
		runForces.polynomicForce(position_x, acceleration_x);
		
		// communicate that single force
		if (world_rank+1 == world_size){MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, 0, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);}
		else{MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, world_rank+1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);}
		if (world_rank == 0){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_size-1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank-1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		
		runIntegration.update_velocity(velocity_x, acceleration_x);
		runIntegration.update_position(position_x, velocity_x);
		runForces.polynomicForce(position_x, acceleration_x);
		
		// communicate that single force
		if (world_rank+1 == world_size){MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, 0, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);}
		else{MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, world_rank+1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);}
		if (world_rank == 0){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_size-1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank-1, 1,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		
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