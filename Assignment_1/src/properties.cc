
#include<vector>
#include<iostream>

using namespace std;

vector<double> getEnergy(const vector<double>& position_x, const vector<double>& velocity_x, const double& a, const double& b, const double& c, const double& mass){
	vector<double> energy_vector;
	double kintetic_energy = 0.0, potential_energy = 0.0;
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
	return energy_vector;
}

void binVelocities(const vector<double>& velocity_x, vector<long>& hist_velocity, const double& max_velocity, const double& min_velocity){
	// bining the velocities by a Bucket sort algorithm
	const int number_particles = velocity_x.size(), buckets = hist_velocity.size();
	const double bucketSize = (max_velocity - min_velocity)/((double)buckets);
	int bucketIndex;
	for (int i=0; i<number_particles; i++){
		if (velocity_x[i] > max_velocity){hist_velocity[buckets-1] += 1;}
		else if (velocity_x[i] < min_velocity){hist_velocity[buckets-1] += 1;}
		else{
			bucketIndex = int((velocity_x[i] - min_velocity)/bucketSize);
			hist_velocity[bucketIndex] += 1;
		}
	}
}

