/*****************************************************************************
 * Lattice.h
 * Headerfile for Lattice.cc
 * ***************************************************************************/
 
#include<vector>
#include<random>

using namespace std;
 
template<class Sweeper>
 class Lattice{
	public:
		Lattice(const Sweeper& Sweep_in, const int& seed_in, const int& L_in, const int& q_in);
		void do_sweep();
		double return_energy(); 
 };