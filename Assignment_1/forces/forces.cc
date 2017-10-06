
#include<vector>

using namespace std;

void polynomicForce(const vector<double>& position_x, vector<double>& acceleration_x, const double& a, const double& b, const double& c, const double& mass){
	double Force;
	int ip1;
	const double mass_inverse=1.0/mass;
	const int number_particles = position_x.size();
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
}
