/*****************************************************************************
 * potentials.cc
 *
 * file to set the initialcondition for different potentials
 * ***************************************************************************/

#include<cmath>
 
double set_q0(const int& potential_type, const double& x){
	double q0;
	if (potential_type == 3){q0=std::exp(-0.5*x*x);}
	else if(potential_type == 4){q0=std::exp(-0.5*x*x);}
	else if(potential_type == 5){q0=0.0;}
	
	return q0;
}

double set_p0(const int& potential_type, const double& x){
	double p0;
	if (potential_type == 3){p0=0.0;}
	else if (potential_type == 4){p0=-x*std::exp(-0.5*x*x);}
	else if (potential_type == 5){p0=std::copysign(1.0,x);}
	
	return p0;
}