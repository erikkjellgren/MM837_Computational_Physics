/*****************************************************************************
 * Sweepers.h
 * Headerfile for Sweepers.cc
 * ***************************************************************************/
 
#include <vector>
#include <random>
 
class Typewriter{
	const int seed, L, q, 
	int Delta_Energy, purposal, Delta_Energy_total, local_energy;
	const double beta;
	double p_accept;
	public:
		Typewriter(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in);
		void operator() (vector<vector<int>>& lattice, int& Delta_Energy_total);
		int reverse_delta_function(const int& spin_i, const int& spin_j);
		void check_purposal(const int& spin_i, const int& spin_j);
};