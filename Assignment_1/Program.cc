
#include<mpi.h>
#include<iostream>
#include<fstream>
#include<cmath>
#include "integrators/integrators.h"
#include "forces/forces.h"
#include "properties/properties.h"
#include "iocontrol/iocontrol.h"
#include "external/json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
	// initialize the MPI
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	// initialize class to control IO
	print_results results(world_rank);
	
	// check inputfile
	if (world_rank==0){results.checkInput(world_size);}
	
	double mass, integration_step, delta, a, b, c, recv_buffer, total_kinetic_energy, total_potential_energy, hist_max_velocity, hist_min_velocity;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global, number_steps, number_particles_local, sample_frequency, right_neighbour, left_neighbour, equilibration_steps, hist_velocity_bins, recv_buffer_int;
	vector<double> position_x, velocity_x, acceleration_x, energy_vector, initial_help_vector;
	vector<int> hist_velocity;
	
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
		sample_frequency = j["sample_frequency"];
		integration_step = j["integration_step"];
		equilibration_steps = j["equilibration_steps"];
		hist_velocity_bins = j["hist_velocity_bins"];
		hist_max_velocity = j["hist_max_velocity"];
		hist_min_velocity = j["hist_min_velocity"];
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
			MPI_Send(&sample_frequency,1,MPI_INT,i,8,MPI_COMM_WORLD);
			MPI_Send(&integration_step,1,MPI_DOUBLE,i,9,MPI_COMM_WORLD);
			MPI_Send(&equilibration_steps,1,MPI_DOUBLE,i,10,MPI_COMM_WORLD);
			MPI_Send(&hist_max_velocity,1,MPI_DOUBLE,i,11,MPI_COMM_WORLD);
			MPI_Send(&hist_min_velocity,1,MPI_DOUBLE,i,12,MPI_COMM_WORLD);
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
		MPI_Recv(&sample_frequency,1,MPI_INT,0,8,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&integration_step,1,MPI_DOUBLE,0,9,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&equilibration_steps,1,MPI_DOUBLE,0,10,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&hist_max_velocity,1,MPI_DOUBLE,0,11,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		MPI_Recv(&hist_min_velocity,1,MPI_DOUBLE,0,12,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	
	// Make vector to store bined velocities
	for (int i=0; i<hist_velocity_bins; i++){
		hist_velocity.push_back(0);
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
	if (world_rank==world_size-1){velocity_x[number_particles_local-1] = sin(2.0*pi*(delta)/((double)number_particles_global));}
	
	// calculate MPI neighbours
	if (world_rank+1==world_size){right_neighbour = 0;}
	else {right_neighbour = world_rank+1;}
	if (world_rank==0){left_neighbour = world_size-1;}
	else {left_neighbour = world_rank-1;}
	
	for (int i=1; i<number_steps+equilibration_steps+1; i++){
		polynomicForce(position_x, acceleration_x, a, b, c, mass);

		MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, right_neighbour, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, left_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		acceleration_x[0] += recv_buffer;
		// The accelerations have been accumulated in the zeroth index at the rank+1 process
		// now the total acceleration is send back to the last index of the rank process (rank-1 now)
		MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, left_neighbour, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, right_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		acceleration_x[number_particles_local-1] = recv_buffer;
		
		
		update_velocity(velocity_x, acceleration_x, integration_step);
		update_position(position_x, velocity_x, integration_step);
		polynomicForce(position_x, acceleration_x, a, b, c, mass);

		
		MPI_Send(&acceleration_x[number_particles_local-1], 1, MPI_DOUBLE, right_neighbour, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, left_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		acceleration_x[0] += recv_buffer;
		// The accelerations have been accumulated in the zeroth index at the rank+1 process
		// now the total acceleration is send back to the last index of the rank process (rank-1 now)
		MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, left_neighbour, 1, MPI_COMM_WORLD);
		MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, right_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		acceleration_x[number_particles_local-1] = recv_buffer;
		
		
		update_velocity(velocity_x, acceleration_x, integration_step);
		
		
		if (i%sample_frequency == 0 && i > equilibration_steps){
			// code calc velocity distribution
			energy_vector = getEnergy(position_x, velocity_x, a, b, c, mass);
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
				results.writeEnergy(total_kinetic_energy, total_potential_energy, (i-equilibration_steps)*integration_step);			
			}
		}
	}
	// code writeout velocity distribution
	if (world_rank != 0){
		for (int i=0; i<hist_velocity_bins; i++){
			MPI_Send(&hist_velocity[i], 1, MPI_INT, 0, i, MPI_COMM_WORLD);
		}
	}
	if (world_rank == 0){
		for (int j=1; j<world_size; j++){
			for (int i=0; i<hist_velocity_bins; i++){
				MPI_Recv(&recv_buffer_int, 1, MPI_INT, j, i, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				hist_velocity[i] += recv_buffer_int;
			}
		}
		results.writeVelocityDistribution(hist_velocity);
	}

	// close output files
	if(world_rank==0){results.close_output_files();}
	MPI_Finalize();
};