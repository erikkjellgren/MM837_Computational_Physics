
#include<mpi.h>
#include<iostream>
#include<cmath>
#include "integrators/integrators.h"
#include "forces/forces.h"
#include "properties/printresults.h"

using namespace std;

int main(){
	// initialize the MPI
	MPI_Init(NULL, NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	
	
	double mass=1.0, integration_step=0.01, delta=0.1, a=1.0, b=0.0, c=0.0, recv_buffer, total_kinetic_energy, total_potential_energy;
	const double pi = 3.141592653589793238462643383279;
	int number_particles_global=1e+8, steps=10, number_particles_local, print_frequency=1, right_neighbour, left_neighbour;
	vector<double> position_x, velocity_x, acceleration_x, energy_vector, initial_help_vector;

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
	
	for (int i=0; i<steps; i++){
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
		
		
		if (i%print_frequency == 0){
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
				cout << total_kinetic_energy << ' ' << total_potential_energy << '\n';				
			}
		}
	}
	MPI_Finalize();
};