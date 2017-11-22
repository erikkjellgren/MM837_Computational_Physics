/*****************************************************************************
 * Lattice.h
 * Headerfile for Lattice.cc
 * ***************************************************************************/
#ifndef _LATTICE_H_
#define _LATTICE_H_
 
#include<vector>
#include<random>

using namespace std;
 
template<class Sweeper>
class Lattice{
	private:
		const int seed, L, q;
		int Energy, Delta_Energy;
		const Sweeper& Sweep;
		mt19937 gen;
		uniform_int_distribution<int> uniform_int_random;
		vector<vector<int>> lattice;
	public:
		Lattice(const Sweeper& Sweep_in, const int& seed_in, const int& L_in, const int& q_in);
		void do_sweep();
		double return_energy(); 
 };
#endif