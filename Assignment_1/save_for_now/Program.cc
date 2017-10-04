
#include<mpi.h>
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
	// initialize the MPI
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	print_results results(0);
	results.checkInput(world_size);
	
	// assign all variables
	double mass, integration_step, delta, a, b, c, recv_buffer, total_kinetic_energy, total_potential_energy;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global, number_steps, number_particles_local, print_frequency;
	vector<double> position_x, velocity_x, acceleration_x, initial_help_vector, energy_vector;
	
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
		integration_step = j["integration_step"];
		// pretty ugly way to send it out. There must be
		// a better solution. Maybe broadcast?
		for (int i=1; i<world_size; i++){
			MPI_Send(&a,1,MPI_DOUBLE,i,1,MPI_COMM_WORLD);
			MPI_Send(&b,1,MPI_DOUBLE,i,2,MPI_COMM_WORLD);
			MPI_Send(&c,1,MPI_DOUBLE,i,3,MPI_COMM_WORLD);
			MPI_Send(&mass,1,MPI_DOUBLE,i,4,MPI_COMM_WORLD);
			MPI_Send(&delta,1,MPI_DOUBLE,i,5,MPI_COMM_WORLD);
			MPI_Send(&number_particles_global,1,MPI_INT,i,6,MPI_COMM_WORLD);
			MPI_Send(&number_steps,1,MPI_INT,i,7,MPI_COMM_WORLD);
			MPI_Send(&print_frequency,1,MPI_INT,i,8,MPI_COMM_WORLD);
		}
	}
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

	
	// Making vector containing start i for the processes.
	// if numer_of_particles differ, between the processes, this is needed.
	// number_particles_local is one higher than the start point since,
	// the end particles of every slice, is present in two processes.
	int check_plus_one = number_particles_global%world_size;
	int start_idx=0;
	for (int i=0; i<world_size; i++){
		if (i < check_plus_one){
			initial_help_vector.push_back(start_idx);
			start_idx += int(number_particles_global/world_size)+1;
			if (i==world_rank){
				number_particles_local = int(number_particles_global/world_size)+1+1;
			}
		}
		else{
			initial_help_vector.push_back(start_idx);
			start_idx += int(number_particles_global/world_size);
			if (i==world_rank){
				number_particles_local = int(number_particles_global/world_size)+1;
			}
		}
	}
	
	// assign number_particles_local
	// Setup the system
	for (int i=initial_help_vector[world_rank]; i<number_particles_local+initial_help_vector[world_rank]; i++){
		position_x.push_back(0.0);
		// fix so the initial velocties are distributed the right way.
		// distribution should be identical for many processes, as for 
		// one process
		velocity_x.push_back(sin(2.0*pi*((double)i+delta)/((double)number_particles_global)));
		acceleration_x.push_back(0.0);
	}
	
	// the last particle of the last process, need to have same condition as the first particle, i.e. i==0
	if (world_rank==world_size-1){position_x[number_particles_local-1] = sin(2.0*pi*(delta)/((double)number_particles_global));}
	
	// initialize all the classes
	// the classes are just used as containers of functions, such
	// that constants dosen't need to be given as argument every time.
	integrators runIntegration(integration_step, number_particles_local);
	Forces runForces(a, b, c, number_particles_local, mass);
	calc_properties properties(number_particles_local, a, b, c, mass);
	
	for (int i=0; i<number_steps; i++){
		// ALL RANKS
		runForces.polynomicForce(position_x, acceleration_x);
		
		// communicate force
		// The zeroth index of a process is the same as the last index of the process with one rank lower_bound
		// first the acceleration is acculamted at the zeroth index.
		if (world_rank+1 == world_size){MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);}
		else{MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, world_rank+1, 1, MPI_COMM_WORLD);}
		if (world_rank == 0){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_size-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[0] += recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank-1, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[0] += recv_buffer;
		}
		// The accelerations have been accumulated in the zeroth index at the rank+1 process
		// now the total acceleration is send back to the last index of the rank process (rank-1 now)
		if (world_rank == 0){MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, world_size-1, 1, MPI_COMM_WORLD);}
		else{MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, world_rank-1, 1, MPI_COMM_WORLD);}
		if (world_rank+1 == world_size){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank+1, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		
		// ALL RANKS
		runIntegration.update_velocity(velocity_x, acceleration_x);
		runIntegration.update_position(position_x, velocity_x);
		runForces.polynomicForce(position_x, acceleration_x);
		
		// communicate force
		if (world_rank+1 == world_size){MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);}
		else{MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, world_rank+1, 1, MPI_COMM_WORLD);}
		if (world_rank == 0){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_size-1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[0] += recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank-1, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[0] += recv_buffer;
		}
		if (world_rank == 0){MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, world_size-1, 1, MPI_COMM_WORLD);}
		else{MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, world_rank-1, 1, MPI_COMM_WORLD);}
		if (world_rank+1 == world_size){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		else {
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, world_rank+1, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			acceleration_x[number_particles_local-1] = recv_buffer;
		}
		
		// ALL RANKS
		runIntegration.update_velocity(velocity_x, acceleration_x);
		
		if (i%print_frequency == 0){
			energy_vector = properties.getEnergy(position_x, velocity_x);
			// communicate energy_vector
			if (world_rank != 0){
				MPI_Send(&energy_vector[0], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
				MPI_Send(&energy_vector[1], 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
			}
			if (world_rank == 0){
				total_kinetic_energy = energy_vector[0];
				total_potential_energy = energy_vector[1];
				for (int i=1; i<world_size; i++){
					MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					total_kinetic_energy += recv_buffer;
					MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
					total_potential_energy += recv_buffer;
				}
				results.writeEnergy(total_kinetic_energy, total_potential_energy);				
			}
		}
	}
	results.close_output_files();
	MPI_Finalize();
};