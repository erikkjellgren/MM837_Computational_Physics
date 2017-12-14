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
		const int rng_seed, L, sweeping_method, initial_lattice;
		const double beta;
		typedef mt19937 random_generator;
		random_generator gen;
		uniform_int_distribution<int> uniform_int_random;
		uniform_int_distribution<int> uniform_int_lattice;
		uniform_real_distribution<double> uniform_random;
		vector<vector<int>> lattice;
		typedef void (Lattice::*fptr)();
		fptr Sweep;
	public:
		Lattice(const int& seed_in, const int& L_in, const double& beta_in, const int& sweeping_method_in, const int& initial_lattice_in);
 };
#endif