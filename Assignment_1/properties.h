
#include<vector>

using namespace std;

class calc_properties{
	int number_particles;
	double a, b, c, mass;
	public:
		calc_properties(const int& number_particles_, const double& a_, const double& b_, const double& c_, const double mass_){
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
			for (int i=0; i<number_particles-1; i++){
				kintetic_energy += velocity_x[i]*velocity_x[i];
				if (a != 0.0){potential_energy += 0.5*a*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
				if (b != 0.0){potential_energy += 1.0/3.0*b*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
				if (c != 0.0){potential_energy += 0.25*c*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1])*(position_x[i] - position_x[i+1]);}
			}
			kintetic_energy *= 0.5*mass;
			energy_vector.push_back(kintetic_energy);
			energy_vector.push_back(potential_energy);
			return energy_vector;
		}
};
