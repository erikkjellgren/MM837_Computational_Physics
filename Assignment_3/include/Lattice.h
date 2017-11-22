/*****************************************************************************
 * Lattice.h
 * Headerfile for Lattice.cc
 * ***************************************************************************/
 
#include <vector>
#include<random>
 
template<class Sweeper>
 class Lattice{
	const int seed, L, q;
	int Energy, Delta_Energy;
	const Sweeper& Sweep;
	public:
		Lattice(const Sweeper& Sweep_in, const int& seed_in, const int& L_in, const int& q_in);
		void do_sweep();
		double return_energy(); 
 };