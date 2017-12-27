/*****************************************************************************
 * Lattice.h
 * Headerfile for Lattice.cc
 * ***************************************************************************/
 
#ifndef _LATTICE_H_
#define _LATTICE_H_
 
#include<vector>
#include<random>
#include<stack>
#include<iostream>

using namespace std;

class Lattice{
	private:
		const int rng_seed, L, sweeping_method, typewriter_frequency;
		const double beta, p_add_cluster;
		long int typewriter_counter, number_accepted, number_purposes;
		typedef mt19937 random_generator;
		random_generator gen;
		uniform_real_distribution<double> uniform_angle_random;
		uniform_int_distribution<int> uniform_int_lattice;
		uniform_real_distribution<double> uniform_random;
		uniform_real_distribution<double> uniform_real_x;
		uniform_int_distribution<int> get_sign;
		vector<vector<double>> lattice;
		vector<double> two_point_corr_vector;
		typedef void (Lattice::*fptr)();
		fptr Sweep;
	public:
		Lattice(const int& seed_in, const int& L_in, const double& beta_in, const int& sweeping_method_in, const int& typewriter_frequency_in, const double& proposal_delta_in);
		void do_sweep();
		void Typewriter();
		void wolff_cluster();
		void Microcanonical();
		void overrelaxation(const int& spin_i, const int& spin_j);
		double return_energy();
		double return_acceptance_ratio();
		vector<vector<double>> return_lattice();
		void two_point_corr();
		vector<double> return_two_point_corr();
};
#endif