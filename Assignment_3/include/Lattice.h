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
		const int rng_seed, L, q, sweeping_method, hybrid_typewrite_freqency, initial_lattice;
		const double beta, p_add_cluster;
		long int hybrid_counter, number_accepted, number_purposes;
		typedef mt19937 random_generator;
		random_generator gen;
		uniform_int_distribution<int> uniform_int_random;
		uniform_int_distribution<int> uniform_int_random_modified;
		uniform_int_distribution<int> uniform_int_lattice;
		uniform_real_distribution<double> uniform_random;
		vector<vector<int>> lattice;
		const vector<double> p_accept_vector;
		typedef void (Lattice::*fptr)();
		fptr Sweep;
	public:
		Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in, const int& hybrid_typewrite_freqency_in, const int& initial_lattice_in);
		void do_sweep();
		double return_energy(); 
		void Typewriter();
		int reverse_delta_function(const int& spin_i, const int& spin_j);
		void check_proposal(const int& spin_i, const int& spin_j, const int& proposal, const int& Delta_Energy);
		void print_conf();
		int make_proposal(const int& lattice_spin);
		void wolff_cluster();
		void hybrid();
		double return_acceptance_ratio();
		double return_magnetization();
 };
#endif