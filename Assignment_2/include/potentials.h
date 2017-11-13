/*****************************************************************************
 * potentials.h 
 * Heavily modified version of forces.h, from course MM837
 *****************************************************************************/

#include<cmath>

double set_q0(const int& potential_type, const double& x);
double set_p0(const int& potential_type, const double& x);

class Potentials { 
	double e, k1, k2;
	int potential_type;

	public: 
		Potentials( const double& e_in, const double& k1_in, const double& k2_in, const int& potential_type_in): 
			e(e_in), k1(k1_in), k2(k2_in), potential_type(potential_type_in) {} 

		double operator() (const double& q, const double& x) const {
			double v;
			if (potential_type == 3){
				v = k1*x*x; 
			}
			else if(potential_type == 4){
				v = k1*x*x + 2.0*k2*x*x*x*x;
			}
			else if(potential_type == 5){
				v = 0;
			}
			
			return (v-e)*q; 
		}
};