/*****************************************************************************
 * Lattice.h
 * Headerfile for Lattice.cc
 * ***************************************************************************/
 
#ifndef _LATTICE_H_
#define _LATTICE_H_
 
#include<vector>
#include<random>

using namespace std;

class Lattice{
	private:
		const int seed, L, q, sweeping_method;
		const double beta;
		int Energy, Delta_Energy, local_energy, Delta_Energy_total, purposal;
		double p_accept;
		mt19937 gen;
		uniform_int_distribution<int> uniform_int_random;
		uniform_real_distribution<double> uniform_random;
		vector<vector<int>> lattice;
		typedef void (Lattice::*fptr)();
		fptr Sweep;
	public:
		Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in);
		void do_sweep();
		double return_energy(); 
		void Typewriter();
		int reverse_delta_function(const int& spin_i, const int& spin_j);
		void check_purposal(const int& spin_i, const int& spin_j);
 };
#endif