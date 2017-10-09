
#include<mpi.h>
#include<vector>

using namespace std;

void polynomicForce(const vector<double>& position_x, vector<double>& acceleration_x, const double& a, const double& b, const double& c, const double& mass, const int& world_rank, const int& world_size){
	double Force, recv_buffer;
	int ip1, right_neighbour, left_neighbour;
	const double mass_inverse=1.0/mass;
	const int number_particles = position_x.size();
	
	// calculate MPI neighbours
	if (world_rank+1==world_size){right_neighbour = 0;}
	else {right_neighbour = world_rank+1;}
	if (world_rank==0){left_neighbour = world_size-1;}
	else {left_neighbour = world_rank-1;}
	
	for (int i=0; i<number_particles; i++){
		acceleration_x[i] = 0.0;
	}
	
	for (int i=0; i<number_particles-1; i++){
		Force = 0.0;
		ip1=i+1;
		if (a != 0.0){Force += a*(position_x[i] - position_x[ip1]);}
		if (b != 0.0){Force += b*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
		if (c != 0.0){Force += c*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
		acceleration_x[i]   -= Force*mass_inverse;
		acceleration_x[ip1] += Force*mass_inverse;
	}
	
	MPI_Send(&acceleration_x[number_particles-1], 1, MPI_DOUBLE, right_neighbour, 1, MPI_COMM_WORLD);
	MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, left_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	acceleration_x[0] += recv_buffer;
	// The accelerations have been accumulated in the zeroth index at the rank+1 process
	// now the total acceleration is send back to the last index of the rank process (rank-1 now)
	MPI_Send(&acceleration_x[0], 1, MPI_DOUBLE, left_neighbour, 1, MPI_COMM_WORLD);
	MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, right_neighbour, 1,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	acceleration_x[number_particles-1] = recv_buffer;
}