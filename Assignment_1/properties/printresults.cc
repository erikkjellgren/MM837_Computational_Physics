
#include<vector>

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
