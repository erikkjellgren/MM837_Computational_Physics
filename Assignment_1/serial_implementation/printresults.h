
#include<vector>

using namespace std;

class getresults{
	int number_particles, ip1;
	double a, b, c, mass;
	public:
		getresults(const int& number_particles_, const double& a_, const double& b_, const double& c_, const double mass_){
			number_particles = number_particles_;
			a = a_;
			b = b_;
			c = c_;
			mass = mass_;
		}
		
		vector<double> getEnergy(const vector<double>& position_x, const vector<double>& velocity_x){
			vector<double> energy_vector;
			double kintetic_energy = 0.0;
			double potential_energy = 0.0;
			for (int i=0; i<number_particles; i++){
				if (i==number_particles-1){ip1=0;}
				else{ip1=i+1;}
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
};