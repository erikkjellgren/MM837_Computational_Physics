
#include<vector>

using namespace std;

class Forces{
	double a, b, c, mass_inverse;
	int number_particles, ip1;
	public:
		Forces(const double& a_, const double& b_, const double& c_, const int& number_particles_, const double& mass_){
			a = a_;
			b = b_;
			c = c_;
			number_particles = number_particles_;
			mass_inverse = 1.0/mass_;
		}
		
		void polynomicForce(const vector<double>& position_x, vector<double>& acceleration_x){
			double Force;
			for (int i=0; i<number_particles; i++){
				acceleration_x[i] = 0.0;
			}
			
			for (int i=0; i<number_particles; i++){
				Force = 0.0;
				if (i==number_particles-1){ip1=0;}
				else{ip1=i+1;}
				if (a != 0.0){Force += a*(position_x[i] - position_x[ip1]);}
				if (b != 0.0){Force += b*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
				if (c != 0.0){Force += c*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1])*(position_x[i] - position_x[ip1]);}
				acceleration_x[i]   -= Force*mass_inverse;
				acceleration_x[ip1] += Force*mass_inverse;
				}
		}
};
