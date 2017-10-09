
#include<mpi.h>
#include<vector>

using namespace std;

vector<double> getEnergy(const vector<double>& position_x, const vector<double>& velocity_x, const double& a, const double& b, const double& c, const double& mass, const int& world_rank, const int& world_size){
	vector<double> energy_vector;
	double kintetic_energy = 0.0, potential_energy = 0.0, recv_buffer;
	int ip1;
	const int number_particles = position_x.size();
	for (int i=0; i<number_particles-1; i++){
		ip1=i+1;
		kintetic_energy += velocity_x[i]*velocity_x[i];
		if (a != 0.0){potential_energy += 0.5*a*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
		if (b != 0.0){potential_energy += 1.0/3.0*b*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
		if (c != 0.0){potential_energy += 0.25*c*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
	}
	kintetic_energy *= 0.5*mass;
	energy_vector.push_back(kintetic_energy);
	energy_vector.push_back(potential_energy);
	
	// communicate energy_vector to rank == 0
	if (world_rank != 0){
		MPI_Send(&energy_vector[0], 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
		MPI_Send(&energy_vector[1], 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
	}
	if (world_rank == 0){
		for (int i=1; i<world_size; i++){
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			energy_vector[0] += recv_buffer;
			MPI_Recv(&recv_buffer, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			energy_vector[1] += recv_buffer;
		}
	}
	return energy_vector;
}

void binVelocities(const vector<double>& velocity_x, vector<long>& hist_velocity, const double& max_velocity, const double& min_velocity){
	// bining the velocities by a Bucket sort algorithm
	const int number_particles = velocity_x.size(), buckets = hist_velocity.size();
	const double bucketSize = (max_velocity - min_velocity)/((double)buckets);
	int bucketIndex;
	// -1, else the shared particles will be counted twice
	for (int i=0; i<number_particles-1; i++){
		if (velocity_x[i] > max_velocity){hist_velocity[buckets-1] += 1;}
		else if (velocity_x[i] < min_velocity){hist_velocity[buckets-1] += 1;}
		else{
			bucketIndex = int((velocity_x[i] - min_velocity)/bucketSize);
			hist_velocity[bucketIndex] += 1;
		}
	}
}

