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
		const int rng_seed, L, q, sweeping_method;
		const double beta;
		int Energy, Delta_Energy, local_energy, purposal, hybrid_counter, hybrid_typewrite_freqency;
		double p_accept, p_add_cluster;
		typedef mt19937 random_generator;
		random_generator gen;
		uniform_int_distribution<int> uniform_int_random;
		uniform_int_distribution<int> uniform_int_lattice;
		uniform_real_distribution<double> uniform_random;
		vector<vector<int>> lattice;
		typedef void (Lattice::*fptr)();
		fptr Sweep;
	public:
		Lattice(const int& seed_in, const int& L_in, const int& q_in, const double& beta_in, const int& sweeping_method_in, const int& hybrid_typewrite_freqency_in);
		void do_sweep();
		double return_energy(); 
		void Typewriter();
		int reverse_delta_function(const int& spin_i, const int& spin_j);
		void check_purposal(const int& spin_i, const int& spin_j);
		void print_conf();
		void make_purposal(const int& lattice_spin);
		void wolff_cluster();
		void hybrid();
 };
#endif